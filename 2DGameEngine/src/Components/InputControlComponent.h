#pragma once
#include "../Component.h"
#include "../Game.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

#include <map>
#include <vector>

const float PLAYER_SPEED = 100.0f;

enum InputAction
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	SHOOT,
	PAUSE,
	QUIT,
	ENUM_ACTION_COUNT
};

struct InputKey
{
	std::vector<SDL_KeyCode> keyCodes;
	InputAction inputAction;
};


class InputControlComponent : public Component
{
	// FUNCTIONS
public:
	InputControlComponent() {};
	
	~InputControlComponent() {};

	//#TODO_ADD_MOVEandCOPY


	void Initialize(Entity* owner) override;
	void Update(float deltaTime) override;
	void Render() override;

private:

	// VARS
public:

private:
	//std::map<InputAction, SDL_KeyCode> _InputMappings;

};