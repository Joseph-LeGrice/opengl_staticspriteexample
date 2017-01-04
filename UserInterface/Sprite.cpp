#include "Sprite.h"
#include <glm/gtx/transform.hpp>

Sprite::Sprite()
{
	m_vertices = new std::vector<Vertex>();
	m_vertices->push_back({ {  1.0f,  1.0f, 0.0f },{ 1.0f, 1.0f } });
	m_vertices->push_back({ { -1.0f,  1.0f, 0.0f },{ 0.0f, 1.0f } });
	m_vertices->push_back({ { -1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f } });
	m_vertices->push_back({ {  1.0f,  1.0f, 0.0f },{ 1.0f, 1.0f } });
	m_vertices->push_back({ { -1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f } });
	m_vertices->push_back({ {  1.0f, -1.0f, 0.0f },{ 1.0f, 0.0f } });
}

Sprite::Sprite(unsigned int spriteIndex, glm::fvec3 position, glm::fvec3 scale) : Sprite()
{
	m_spriteIndex = spriteIndex;
	SetPosition(position);
	SetScale(scale);
}

Sprite::~Sprite()
{
	delete m_vertices;
}

void Sprite::SetPosition(glm::fvec3 position)
{
	m_translation = glm::translate(position);
}

void Sprite::SetScale(glm::fvec3 scale)
{
	m_scale = glm::scale(scale);
}

glm::fmat4 Sprite::GetTransformation()
{
	return m_translation * m_scale;
}

std::vector<Vertex>* Sprite::GetVertices()
{
	return m_vertices;
}

unsigned int Sprite::GetSpriteIndex()
{
	return m_spriteIndex;
}
