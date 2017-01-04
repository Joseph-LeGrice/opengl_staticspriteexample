#pragma once

#include <vector>
#include <gl\glew.h>
#include "Sprite.h"
#include "Shader.h"
#include "SpriteAtlasManager.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render();

private:
	static const int BUFFER_COUNT = 1;
	static const int BUFFER_INDEX_STATIC = 0;
	static const int BUFFER_INDEX_DYNAMIC = 1;

	const int VERTEX_ATTRIBUTE_VERTICES = 0;
	const int VERTEX_ATTRIBUTE_UVS = 1;
	
	const float ORTHO_SIZE = 20.0f;
	const int NUM_STATIC_SPRITES = 100;

	int m_numberOfStaticVerts;

	GLuint m_vertexArrayObject;
	GLuint m_vertexBuffers[BUFFER_COUNT];
	
	Shader *m_shader;
	SpriteAtlasManager *m_atlasManager;

	std::vector<Sprite*> *m_staticSprites;

	void InitializeStaticGeometry(); 
	glm::fmat4 Renderer::GetMVP(glm::fmat4 model);
};

