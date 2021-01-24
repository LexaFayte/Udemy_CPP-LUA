#include "Player.h"
#include "Game.h"
#include "AssetManager.h"
#include "Components/TransformComponent.h"
#include "Components/InputControlComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/ColliderComponent.h"
#include "Constants.h"
#include <iostream>


Player::Player() : Entity(Game::GetEntityManager(), "Player", LayerType::PLAYER)
{	
	_transformComponent = &AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	_spriteComponent = &AddComponent<SpriteComponent>(Game::GetAssetManager()->GetTexture("chopper-texture"), 2, 90, true, false);
	_inputControlComponent = &AddComponent<InputControlComponent>();
	_colliderComponent = &AddComponent<ColliderComponent>("player", CollisionType::PLAYER, 240, 106, 32, 32);
	internalInitialize();

	_manager.AddExistingEntity(*this);
}

Player::~Player()
{
	//_colliderComponent->OnCollision -= _collisionFunction;
}

void Player::internalInitialize()
{
	//std::function<void()> CollisionFunction = [this]() { OnCollisionCallback(); };
	//_collisionFunction = _colliderComponent->CreateCallBackFunction(CollisionFunction);
	//_colliderComponent->OnCollision += _collisionFunction;
	
	auto& collisionParameters = _colliderComponent->GetCollisionParameters();
	collisionParameters.changeCollisionLayerFlag(CollisionLayer::PLAYER, false);
	collisionParameters.changeCollisionLayerFlag(CollisionLayer::LEVEL_TRIGGER, true);	
}

//void Player::OnCollisionCallback()
//{
//	auto collisions = _colliderComponent->collisionsThisUpdate;
//
//	for(auto& entity : collisions)
//	{
//		std::cerr << entity->name << std::endl;
//	}
//}

