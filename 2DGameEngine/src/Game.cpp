#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Entity.h"
#include "EntityManager.h"
#include "AssetManager.h"
#include "Components/InputControlComponent.h"

#include "Player.h"
#include "Map.h"
#include "Components/ColliderComponent.h"
#include "Components/TextLabelComponent.h"
#include "Components/ProjectileEmitterComponent.h"

//#include "ECS/Entity/PureEntity.h"





// Static member variables
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
EntityManager Game::_entityManager;
AssetManager* Game::_assetManager = nullptr;
SDL_Renderer* Game::_renderer = nullptr;

Game::Game()
{

}

Game::~Game()
{

}

void Game::LoadLevel(int levelNumber)
{
	//#TODO
	//create a level loading manager

	sol::state luaState;
	luaState.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);


	std::string levelName = "Level" + std::to_string(levelNumber);
	luaState.script_file("./assets/scripts/" + levelName + ".lua");

	sol::table levelData = luaState[levelName];
	
	//load assets from lua script
	sol::table levelAssets = levelData["assets"];
	unsigned int assetIndex = 0;
	while(true)
	{
		sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
		if(existsAssetIndexNode == sol::nullopt)
		{
			break;
		}

		sol::table asset = levelAssets[assetIndex];
		std::string assetType = asset["type"];
		if(assetType.compare("texture") == 0)
		{
			std::string assetId = asset["id"];
			std::string assetFile = asset["file"];
			_assetManager->AddTexture(assetId, assetFile.c_str());
		}
		else if(assetType.compare("font") == 0)
		{
			std::string assetId = asset["id"];
			std::string assetFile = asset["file"];			
			_assetManager->AddFont(assetId, assetFile.c_str(), static_cast<int>(asset["fontSize"]));
		}

		assetIndex++;
	}

	// load map
	sol::table levelMap = levelData["map"];
	std::string mapTextureId = levelMap["textureAssetId"];
	std::string mapFile = levelMap["file"];

	_JungleMap = new Map(mapTextureId, static_cast<int>(levelMap["scale"]), static_cast<int>(levelMap["tileSize"]));
	_JungleMap->LoadMap(mapFile, levelMap["mapSizeX"], levelMap["mapSizeY"]);

	// CREATE ENTITIES (player, enemies, etc.)
	// TEST
	Entity& TankEntity = _entityManager.AddEntity("Tank", LayerType::ENEMIES);
	TankEntity.AddComponent<TransformComponent>(150, 495, 5, 0, 32, 32, 1);
	TankEntity.AddComponent<ColliderComponent>("enemy", CollisionType::ENEMY, 150, 495, 32, 32);
	TankEntity.AddComponent<SpriteComponent>("tank-big-right-texture");

	Entity& projectileEntity(_entityManager.AddEntity("projectile", LayerType::PROJECTILES));
	projectileEntity.AddComponent<TransformComponent>(150 + 16, 495 + 16, 0, 0, 4, 4, 1);
	projectileEntity.AddComponent<ColliderComponent>("projectile", CollisionType::PROJECTILE, 150 + 16, 495 + 16, 4, 4);
	projectileEntity.AddComponent<SpriteComponent>("projectile-texture");
	projectileEntity.AddComponent<ProjectileEmitterComponent>(50, 270, 200, true);//speed, angle, range (how many pixels before it dies), loop (keep firing?)

	Entity& heliPad = _entityManager.AddEntity("HeliPad", LayerType::ENVIRONMENT);
	heliPad.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
	heliPad.AddComponent<ColliderComponent>("LEVEL_COMPLETE", CollisionType::LEVEL_COMPLETE, 470, 420, 32, 32);
	heliPad.AddComponent<SpriteComponent>("heliport-texture");

	Entity& labelLevelName(_entityManager.AddEntity("LabelLevelName", LayerType::UI));
	labelLevelName.AddComponent<TextLabelComponent>(10, 10, "First Level", "charriot-font", COLOR_WHITE);

	Player* playerEntity = new Player();
	if(!playerEntity)
	{
		std::cerr << "Creation of Player failed" << std::endl;
	}
		
	//#TODO
	//create a debug logger

	//std::cout << "Test Entity name: " << testEntity.name << std::endl;
	//std::cout << "Components Attached:\n" << typeid(*testEntity._components[0]).name() << std::endl;
	
	// TEST

}

void Game::Initialize(int windowWitdth, int windowHeight)
{

	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error Initializing SDL" << std::endl;
		return;
	}

	if(TTF_Init() != 0)
	{
		std::cerr << "Error Initializing SDL TFF" << std::endl;
		return;
	}
	
	_windowWidth = windowWitdth;
	_windowHeight = windowHeight;

	// Create SDL Window
	_window = SDL_CreateWindow(
		"SDL WINDOW HERE", // window title
		SDL_WINDOWPOS_CENTERED, // X
		SDL_WINDOWPOS_CENTERED, // Y
		_windowWidth, // window height
		_windowHeight, // window width
		0 // SDL_WINDOW_BORDERLESS
		);

	if(!_window)
	{
		std::cerr << "Error creating SDL window" << std::endl;
		return;
	}
	
	// Create SDL Render Context
	_renderer =SDL_CreateRenderer(
		_window, // window context
		-1, // default driver for display
		0 // no options
		);

	if (!_renderer)
	{
		std::cerr << "Error creating SDL renderer" << std::endl;
		return;
	}

	_assetManager = new AssetManager(&_entityManager);

	LoadLevel(1);

	_isRunning = true;
}

void Game::ProcessInput()
{
	SDL_PollEvent(&event);

	switch(event.type)
	{
	case SDL_QUIT:
		_isRunning = false;
		break;

	case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_ESCAPE)
		{
			_isRunning = false;
		}
		break;

	default:
		break;
	}
}

void Game::Update()
{
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - _ticksLastFrame);
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
		SDL_Delay(timeToWait);

	// setup delta time
	float deltaTime = (SDL_GetTicks() - _ticksLastFrame) / 1000.f;
	
	//clamp delta time
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	//update ticks
	_ticksLastFrame = SDL_GetTicks();

	if (_entityManager.HasEntities())
		_entityManager.Update(deltaTime);

	HandleCameraMovement();
	CheckCollisions();

}

void Game::HandleCameraMovement()
{
	//#TODO_REFACTOR: FIX THIS
	TransformComponent* transComp = _entityManager.GetEntitiesByLayer(LayerType::PLAYER)[0]->GetComponent<TransformComponent>();
	
	if(transComp)
	{
		camera.x = transComp->position.x - (WINDOW_WIDTH/2);
		camera.y = transComp->position.y - (WINDOW_HEIGHT/2);

		//#TODO_REFACTOR: FIX THIS - if map scale is 1, we go beyond map bounds; also need to clamp player to not move beyond edges of sceeen
		//clamp to edges of map
		camera.x = camera.x < 0 ? 0 : camera.x;
		camera.y = camera.y < 0 ? 0 : camera.y;

		camera.x = camera.x > camera.w ? camera.w : camera.x;
		camera.y = camera.y > camera.h ? camera.h : camera.y;
	}
}

void Game::CheckCollisions()
{
	//#TODO_REFACTOR: FIX THIS; tell the manager to get all the entities to check their collisions
	auto colliderTag = _entityManager.CheckEntityCollisions(*(_entityManager.GetEntitiesByLayer(LayerType::PLAYER)[0]));
	
	if (colliderTag != CollisionType::NONE)
	{
		if(colliderTag == CollisionType::LEVEL_COMPLETE)
		{
			std::cout << "Next Level" << std::endl;
			_isRunning = false;
		}
		else if( colliderTag == CollisionType::ENEMY || colliderTag == CollisionType::PROJECTILE)
		{
			std::cout << "DEAD" << std::endl;
			_isRunning = false;
		}
	}
	
}

void Game::Render()
{
	//set BG colour
	SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
	
	// clear back buffer
	SDL_RenderClear(_renderer);

	// RENDER STUFF HERE
	if(_entityManager.HasEntities())
		_entityManager.Render();

	// present to screen (swap front buffer w/ back buffer)
	SDL_RenderPresent(_renderer);
}

void Game::Shutdown()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

AssetManager* const Game::GetAssetManager() noexcept
{
	return _assetManager;
}

EntityManager& const Game::GetEntityManager() noexcept
{
	return _entityManager;
}

