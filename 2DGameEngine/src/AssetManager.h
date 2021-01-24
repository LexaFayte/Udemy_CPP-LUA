#pragma once
#include <map>
#include <string>
#include <SDL_ttf.h>
#include "TextureManager.h"
#include "FontManager.h"
#include "EntityManager.h"

class AssetManager
{
	// FUNCTIONS
public:
	AssetManager() {};
	AssetManager(EntityManager* manager);
	~AssetManager();
	
	void ClearData();
	void AddTexture(std::string textureId, const char* filePath);
	SDL_Texture* GetTexture(std::string textureId);
	
	void AddFont(std::string fontId, const char* filePath, int fontSize);
	TTF_Font* GetFont(std::string fontId);
	



private:

	// VARS
public:

private:
	EntityManager* _manager = nullptr;
	std::map<std::string, SDL_Texture*> _textures;
	std::map<std::string, TTF_Font*> _fonts;
};