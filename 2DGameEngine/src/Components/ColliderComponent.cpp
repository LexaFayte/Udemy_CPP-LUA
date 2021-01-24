#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "../Entity.h"
#include "../Game.h"
#include <vector>

ColliderComponent::ColliderComponent(std::string colliderTag, CollisionType collisionType, int x, int y, int width, int height) :
	colliderTag(colliderTag),
	collisionType(collisionType)
{
	collider = {x,y,width,height};
}

ColliderComponent::~ColliderComponent()
{

}

void ColliderComponent::Initialize(Entity* owner)
{
	_owner = owner;
	if(_owner && _owner->HasComponent<TransformComponent>())
	{
		transform = _owner->GetComponent<TransformComponent>();
		sourceRect = { 0,0,transform->width,transform->height };
		destRect = { collider.x, collider.y,collider.w,collider.h };
	}
}

void ColliderComponent::Update(float deltaTime)
{
	//check collisions here for self
	//auto entityManager = Game::GetEntityManager();
	//auto otherEntities = entityManager.GetEntitiesByComponent<ColliderComponent>();
	//bool collision = false;

	//for (auto& entityOther : otherEntities)
	//{
	//	auto otherColliderComponent = entityOther->GetComponent<ColliderComponent>();
	//	CollisionLayer otherCollisionLayer = otherColliderComponent->GetCollisionParameters().entityLayer;
	//	
	//	if (*entityOther != *_owner && _collisionParameters.getCollisionLayerFlag(otherCollisionLayer))
	//	{
	//		if (Collision::InternalCheckAABBCollision(otherColliderComponent->collider, collider))
	//		{
	//			collision = true;
	//			collisionsThisUpdate.push_back(entityOther);
	//		}
	//	}
	//}

	//if(collision)
	//{
	//	OnCollision.Execute();
	//}
	
	// update with the transform of the entity
	collider.x = static_cast<int>(transform->position.x);
	collider.y = static_cast<int>(transform->position.y);
	collider.w = transform->width * transform->scale;
	collider.h = transform->height * transform->scale;
	destRect.x = collider.x - Game::camera.x;
	destRect.x = collider.y - Game::camera.y;
}

void ColliderComponent::Render()
{
	//IF DEBUG, render collider comp
	//SDL_RenderDrawRect(Game::GetRenderer(), &collider);
}

