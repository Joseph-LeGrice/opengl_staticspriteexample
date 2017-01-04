#pragma once

#include <vector>
#include <string>
#include <gl/glew.h>
#include <glm/glm.hpp>

struct SpriteInfo
{
	std::string spriteName;
	glm::fvec2 uv_min;
	glm::fvec2 uv_max;
};

class SpriteAtlasManager
{
public:
	SpriteAtlasManager();
	~SpriteAtlasManager();

	const SpriteInfo* GetSpriteInfo(std::string spriteId);
	const SpriteInfo* GetSpriteInfo(int spriteIndex);

	unsigned int TotalNumberOfSprites();
private:
	std::vector<SpriteInfo> *m_allSpriteInfo;
	GLuint m_spriteTexture;

	void LoadTexture();
	void LoadAtlasData();
};

