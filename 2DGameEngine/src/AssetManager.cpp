#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* manager)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::ClearData()
{
	for(auto it = _textures.begin(); it != _textures.end(); ++it)
	{
		SDL_DestroyTexture(it->second);
	}

	_textures.clear();

	for (auto it = _fonts.begin(); it != _fonts.end(); ++it)
	{
		TTF_CloseFont(it->second);
	}

	_fonts.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath)
{
	_textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId)
{
	if(_textures.find(textureId) != _textures.end())
	{
		return _textures[textureId];
	}

	return nullptr;
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize)
{
	_fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontId)
{
	if (_fonts.find(fontId) != _fonts.end())
	{
		return _fonts[fontId];
	}

	return nullptr;
}

