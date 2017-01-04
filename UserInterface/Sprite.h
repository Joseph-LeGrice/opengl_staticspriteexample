#pragma once

#include <vector>
#include <string>
#include <glm\glm.hpp>
#include <gl\glew.h>

struct Vertex
{
	glm::fvec3 position;
	glm::fvec2 uv;
};

class Sprite
{
public:
	Sprite();
	Sprite(unsigned int spriteIndex, glm::fvec3 position, glm::fvec3 scale);
	~Sprite();

	unsigned int GetSpriteIndex();
	void SetPosition(glm::fvec3);
	void SetScale(glm::fvec3);

	glm::fmat4 Sprite::GetTransformation();
	std::vector<Vertex>* GetVertices();

private:
	unsigned int m_spriteIndex;
	std::vector<Vertex> *m_vertices;

	glm::fmat4 m_translation;
	glm::fmat4 m_scale;
};

