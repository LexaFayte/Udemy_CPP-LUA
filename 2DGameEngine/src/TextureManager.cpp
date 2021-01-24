#include "TextureManager.h"
#include "Game.h"

// ======================================================================================================
// #TEXTURE_MANAGER_FUNCTIONS
// ======================================================================================================
SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* surface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), surface);
	SDL_FreeSurface(surface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::GetRenderer(), texture, &source, &dest, 0.0f, NULL, flip);
}
