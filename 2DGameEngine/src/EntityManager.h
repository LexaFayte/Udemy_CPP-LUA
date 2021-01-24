#pragma once
#include <vector>
#include <string>
#include "Constants.h"

class Entity;

class EntityManager
{
	// FUNCTIONS
public:
	EntityManager()
	{

	}

	~EntityManager()
	{

	}

	void ClearData();
	void Update(float deltaTime);
	void Render();
	bool HasEntities();

	Entity& AddEntity(std::string EntityName, LayerType layer);
	void AddExistingEntity(Entity& entity);
	std::vector<Entity*> GetEntities() const;
	std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
	
	template<typename T>
	std::vector<Entity*> GetEntitiesByComponent() const;
	
	unsigned int GetEntityCount() const noexcept;

	CollisionType CheckEntityCollisions(Entity& entity) const;

private:
	void DestroyInactiveEntities();

	//VARS
public:

private:
	std::vector<Entity*> _entities;

};
