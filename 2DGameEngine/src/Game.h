#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../libs/sol/sol.hpp"

class EntityManager;
class AssetManager;
class Map;

class Game
{
	// functions
public:
	Game();
	~Game();
	
	void LoadLevel(int levelNumber);
	void Initialize(int windowWitdth, int windowHeight);
	void ProcessInput();
	void Update();
	void Render();
	void Shutdown();

	inline bool IsRunning() const noexcept { return _isRunning; }
	inline static SDL_Renderer* const GetRenderer() noexcept { return _renderer; }
	static AssetManager* const GetAssetManager() noexcept;
	static EntityManager& const GetEntityManager() noexcept;

private:
	void HandleCameraMovement();
	void CheckCollisions();

	// Variables
public:
	static SDL_Event event;
	static SDL_Rect camera;

private:
	bool _isRunning = false;
	int _windowWidth = 0;
	int _windowHeight = 0;
	int _ticksLastFrame = 0;


	SDL_Window* _window = nullptr;
	Map* _JungleMap = nullptr; // #TODO_REFACTOR: move somewhere else
	static SDL_Renderer* _renderer;
	static AssetManager* _assetManager;
	static EntityManager _entityManager;
};