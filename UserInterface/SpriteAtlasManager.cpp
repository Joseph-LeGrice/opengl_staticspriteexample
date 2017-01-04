#include "SpriteAtlasManager.h"

#include <fstream>
#include "FreeImage.h"
#include "json.hpp"

SpriteAtlasManager::SpriteAtlasManager()
{
	m_allSpriteInfo = new std::vector<SpriteInfo>();
	LoadTexture();
	LoadAtlasData();
}


SpriteAtlasManager::~SpriteAtlasManager()
{
	delete m_allSpriteInfo;
	glDeleteTextures(1, &m_spriteTexture);
}


const SpriteInfo* SpriteAtlasManager::GetSpriteInfo(std::string spriteId)
{
	for (SpriteInfo si : *m_allSpriteInfo)
	{
		if (si.spriteName == spriteId)
		{
			return &si;
		}
	}
	return nullptr;
}

const SpriteInfo* SpriteAtlasManager::GetSpriteInfo(int spriteIndex)
{
	return &m_allSpriteInfo->at(spriteIndex);
}

unsigned int SpriteAtlasManager::TotalNumberOfSprites()
{
	return m_allSpriteInfo->size();
}

void SpriteAtlasManager::LoadTexture()
{
	glGenTextures(1, &m_spriteTexture);
	glBindTexture(GL_TEXTURE_2D, m_spriteTexture);

	FIBITMAP *img = FreeImage_Load(FIF_PNG, "TestAtlas.png", PNG_DEFAULT);
	int w = FreeImage_GetWidth(img);
	int h = FreeImage_GetHeight(img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, FreeImage_GetBits(img));
	FreeImage_Unload(img);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void SpriteAtlasManager::LoadAtlasData()
{
	std::ifstream spriteDataFile("TestAtlasData.json");
	if (spriteDataFile.is_open())
	{
		nlohmann::json spriteDataJson;
		spriteDataFile >> spriteDataJson;

		for (auto& element : spriteDataJson)
		{
			SpriteInfo si;
			si.spriteName = element["spriteName"].get<std::string>();
			si.uv_min = glm::fvec2(element["uv_min"]["x"], element["uv_min"]["y"]);
			si.uv_max = glm::fvec2(element["uv_max"]["x"], element["uv_max"]["y"]);

			m_allSpriteInfo->push_back(si);
		}
		spriteDataFile.close();
	}
}
