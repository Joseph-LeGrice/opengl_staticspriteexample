#include "Renderer.h"

#include <cstdlib>
#include <cstddef>
#include <time.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


Renderer::Renderer()
{
	m_shader = new Shader();
	m_atlasManager = new SpriteAtlasManager();
	m_staticSprites = new std::vector<Sprite*>();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(BUFFER_COUNT, m_vertexBuffers);

	for (int i = 0; i < BUFFER_COUNT; i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffers[i]);

		glEnableVertexAttribArray(VERTEX_ATTRIBUTE_VERTICES);
		glVertexAttribPointer(VERTEX_ATTRIBUTE_VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

		glEnableVertexAttribArray(VERTEX_ATTRIBUTE_UVS);
		glVertexAttribPointer(VERTEX_ATTRIBUTE_UVS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
	}

	InitializeStaticGeometry();
}


Renderer::~Renderer()
{
	delete m_shader;
	delete m_atlasManager;

	for (Sprite *s : *m_staticSprites)
	{
		delete s;
	}
	delete m_staticSprites;

	glDisableVertexAttribArray(VERTEX_ATTRIBUTE_VERTICES);
	glDisableVertexAttribArray(VERTEX_ATTRIBUTE_UVS);

	glDeleteBuffers(BUFFER_COUNT, m_vertexBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Renderer::Render()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::fmat4 mvp = GetMVP(glm::fmat4(1.0f));
	m_shader->SetMVP(mvp);
	glDrawArrays(GL_TRIANGLES, 0, m_numberOfStaticVerts);
}

void Renderer::InitializeStaticGeometry()
{
	srand(time(NULL));
	for (int i = 0; i < NUM_STATIC_SPRITES; i++)
	{
		unsigned int spriteIndex = rand() % m_atlasManager->TotalNumberOfSprites();

		glm::fvec3 position = glm::fvec3();
		position.x = rand() % (int)ORTHO_SIZE - 0.5f * ORTHO_SIZE;
		position.y = rand() % (int)ORTHO_SIZE - 0.5f * ORTHO_SIZE;

		glm::fvec3 scale = glm::fvec3(1.0f, 1.0f, 1.0f);
		m_staticSprites->push_back(new Sprite(spriteIndex, position, scale));
	}

	std::vector<Vertex> allVerts;
	for (Sprite *s : *m_staticSprites)
	{
		glm::fmat4 modelTransformation = s->GetTransformation();
		std::vector<Vertex> spriteVerts = *s->GetVertices();
		
		const SpriteInfo *si = m_atlasManager->GetSpriteInfo(s->GetSpriteIndex());
		glm::fvec2 uvDiff = si->uv_max - si->uv_min;

		for (Vertex v : spriteVerts)
		{
			glm::fvec4 transformedPosition = modelTransformation * glm::fvec4(v.position.x, v.position.y, v.position.z, 1.0f);
			glm::fvec2 transformedUV = si->uv_min + v.uv * uvDiff;
			
			Vertex transformedVert;
			transformedVert.position = glm::fvec3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
			transformedVert.uv = transformedUV;

			allVerts.push_back(transformedVert);
		}
	}
	
	m_numberOfStaticVerts = allVerts.size();
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffers[BUFFER_INDEX_STATIC]);
	glBufferData(GL_ARRAY_BUFFER, allVerts.size() * sizeof(Vertex), &allVerts[0], GL_STATIC_DRAW);
}

glm::fmat4 Renderer::GetMVP(glm::fmat4 model)
{
	float halfOrtho = ORTHO_SIZE / 2;
	glm::fmat4 projection = glm::ortho(-halfOrtho, halfOrtho, -halfOrtho, halfOrtho, 0.0f, 1000.0f);
	glm::fmat4 view = glm::fmat4(1.0f);

	return projection * view * model;
}
