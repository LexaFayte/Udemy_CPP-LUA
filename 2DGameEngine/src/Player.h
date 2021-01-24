#pragma once
#include "Entity.h"
#include <functional>

class TransformComponent;
class SpriteComponent;
class InputControlComponent;
class ColliderComponent;

class Player : public Entity
{
	// FUNCTIONS
public:
	Player();
	~Player();

private:
	void internalInitialize();
	//void OnCollisionCallback();

	// VARS
public:
private:
	TransformComponent* _transformComponent = nullptr;
	SpriteComponent* _spriteComponent = nullptr;
	InputControlComponent* _inputControlComponent = nullptr;
	ColliderComponent* _colliderComponent = nullptr;

	//CallBackFunction _collisionFunction;
};