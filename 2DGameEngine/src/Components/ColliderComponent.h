#pragma once
#include <SDL.h>
#include <string>
#include "../Component.h"
#include "../Constants.h"
#include "../Collision.h"

class TransformComponent;

class ColliderComponent : public Component
{
	// FUNCTIONS
public:
	//TODO_REFACTOR: I don't like the collider tag being a string
	ColliderComponent(std::string colliderTag, CollisionType collisionType, int x, int y, int width, int height);
	~ColliderComponent();


	void Initialize(Entity* owner) override;
	void Update(float deltaTime) override;
	void Render() override;

	CollisionParameters& GetCollisionParameters()
	{
		return _collisionParameters;
	}

	//CallBackFunction CreateCallBackFunction(std::function<void()>& fn)
	//{
	//	CallBackFunction function(std::forward<decltype(fn)>(fn), _TicketCounter);
	//	return function;
	//}

private:

	// VARS
public:
	std::string colliderTag;
	CollisionType collisionType = CollisionType::NONE;
	SDL_Rect collider;
	SDL_Rect sourceRect;
	SDL_Rect destRect;
	TransformComponent* transform = nullptr;

	//_CollisionCallBack::CallBack OnCollision;
	//std::vector<Entity*> collisionsThisUpdate;

private:
	//int _TicketCounter = 0;
	CollisionParameters _collisionParameters;

};

