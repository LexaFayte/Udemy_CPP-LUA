#include "EntityManager.h"
#include "Entity.h"
#include "Collision.h"
#include "Components/ColliderComponent.h"
#include "Components/InputControlComponent.h"

void EntityManager::ClearData()
{
	for(auto& entity : _entities)
	{
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (auto& entity : _entities)
	{
		entity->Update(deltaTime);
	}

	DestroyInactiveEntities();
}

void EntityManager::Render()
{
	//#TODO_REFACTOR: FIX THIS (OPTIMIZE)
	for(int layerNum = 0; layerNum < static_cast<int>(LayerType::LAYER_COUNT); ++layerNum)
	{
		for(auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNum)))
		{
			entity->Render();
		}
	}
}

bool EntityManager::HasEntities()
{
	return (_entities.size() > 0);
}

Entity& EntityManager::AddEntity(std::string EntityName, LayerType layer)
{
	_entities.emplace_back(new Entity(*this, EntityName, layer));
	return *_entities.back();
}

void EntityManager::AddExistingEntity(Entity& entity)
{
	_entities.push_back(&entity);
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return _entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
	//#TODO_REFACTOR: FIX THIS OPTIMIZE
	std::vector<Entity*> selectedEntities;
	for(auto& entity : _entities)
	{
		if(entity->layer == layer)
		{
			selectedEntities.push_back(entity);
		}
	}
	return selectedEntities;
}

template<typename T>
std::vector<Entity*> EntityManager::GetEntitiesByComponent() const
{
	//#TODO_REFACTOR: FIX THIS OPTIMIZE
	std::vector<Entity*> selectedEntities;
	for (auto& entity : _entities)
	{
		if (entity->HasComponent<T>())
		{
			selectedEntities.push_back(entity);
		}
	}
	return selectedEntities;
}

unsigned int EntityManager::GetEntityCount() const noexcept
{
	return _entities.size();
}

// #TODO_REFACTOR: I don't like this; honestly, we should return all the things we are colliding with
// each entity should handle it's own collisions (like "what happens to ME if I had a collision?")
// also think about having an "ignore" list - ignore this collision layer type 
// i.e. projectile ignore player collision layer if that projectile was spawned by the player
CollisionType EntityManager::CheckEntityCollisions(Entity& entity) const
{
	ColliderComponent* myCollider = entity.GetComponent<ColliderComponent>();
	for (auto& entityOther : _entities)
	{
		if (*entityOther != entity && entityOther->HasComponent<ColliderComponent>())
		{
			ColliderComponent* otherCollider = entityOther->GetComponent<ColliderComponent>();
			
			// this whole collisionData thing is dumb; 
			// was thinking something like UE4 collision data - returning a resulting struct
			CollisionData collisionData;
			collisionData.entityCollisionTypeA = myCollider->collisionType;
			collisionData.entityCollisionTypeB = otherCollider->collisionType;
			
			
			Collision::CheckAABBCollisions(myCollider->collider, otherCollider->collider, collisionData);
			if(collisionData.isColliding)
			{
				return collisionData.collisionTypeResult; // <-- this is dumb
			}
		}
	}

	return CollisionType::NONE;
}

void EntityManager::InputReceived(SDL_Event e, bool keyDown)
{
	for (auto& entity : _entities)
	{
		if (entity->HasComponent<InputControlComponent>())
		{
			auto* inputControl = entity->GetComponent<InputControlComponent>();
			if (keyDown)
			{
				inputControl->OnKeyDown(e.key.keysym.sym);
			}
			else
			{
				inputControl->OnKeyUp(e.key.keysym.sym);
			}
		}
	}
}

void EntityManager::DestroyInactiveEntities()
{
	// loop backwards so we don't try to access incorrect elements;
	// vector.erase() will shift values everytime it erases
	for(int i = _entities.size() - 1; i >= 0; --i)
	{
		if(!_entities[i]->IsActive())
		{
			_entities.erase(_entities.begin() + i);
		}
	}
}