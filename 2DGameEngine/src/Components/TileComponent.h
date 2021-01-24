#pragma once
#include <string>
#include <SDL.h>
#include "../../libs/glm/glm.hpp"
#include "../Component.h"
#include "../AssetManager.h"
#include "../Game.h"


class TileComponent : public Component
{
	// FUNCTIONS
public:
	TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string textureId) :
		texture(Game::GetAssetManager()->GetTexture(textureId))
	{
		sourceRect.x = sourceRectX;
		sourceRect.y = sourceRectY;
		sourceRect.w = tileSize;
		sourceRect.h = tileSize;

		destRect.x = x;
		destRect.y = y;
		destRect.w = tileSize * tileScale;
		destRect.h = tileSize * tileScale;

		position.x = x;
		position.y = y;
	};
	
	~TileComponent() 
	{
		SDL_DestroyTexture(texture);
	};

	void Initialize(Entity* owner) override
	{
		_owner = owner;
	}
	
	void Update(float deltaTime) override
	{
		// update tiles based on camera movement
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}
	
	void Render() override
	{
		TextureManager::Draw(texture, sourceRect, destRect, SDL_RendererFlip::SDL_FLIP_NONE);
	}
	

private:

	// VARS
public:
	SDL_Texture* texture = nullptr;
	SDL_Rect sourceRect;
	SDL_Rect destRect;
	glm::vec2 position;
};