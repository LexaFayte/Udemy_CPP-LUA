#pragma once
#include <SDL.h>

class TextureManager
{
	// FUNCTIONS
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, SDL_RendererFlip flip);;

private:

};