#pragma once
#include <SDL_pixels.h>

enum class LayerType
{
	TILEMAP = 0,
	ENVIRONMENT,
	PLAYER,
	ENEMIES,
	PROJECTILES,
	UI,

	LAYER_COUNT
};

enum class CollisionType
{
	NONE = 0,
	PLAYER,
	ENEMY,
	PROJECTILE,
	ENVIRONMENT,
	LEVEL_COMPLETE,

	COLLISION_TYPE_COUNT
};

const unsigned int WINDOW_HEIGHT = 600;
const unsigned int WINDOW_WIDTH = 800;

const unsigned int FRAMERATE = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FRAMERATE;

const SDL_Color COLOR_WHITE = { 255, 255, 255, 255 };
const SDL_Color COLOR_GREEN = { 0, 255, 0, 255 };
