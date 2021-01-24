#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"

unsigned int UniqueID::nextID = 0;

Entity::Entity(EntityManager& manager) : _manager(manager)
{
	_isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer) : _manager(manager), name(name), layer(layer)
{
	_isActive = true;
}

Entity::Entity(const Entity& other) :
	name(other.name),
	_manager(other._manager),
	_components(other._components)
{

}

Entity::Entity(Entity&& other) noexcept : name(std::exchange(other.name, "")), _manager(other._manager), _components(std::move(other._components))
{
	other.name = "";
	other._components.clear();
}

Entity& Entity::operator=(Entity&& other)
{
	if (this != &other)
	{
		name = std::exchange(other.name, "");
		_manager = other._manager;
		_components = std::move(other._components);
	}

	return *this;
}

Entity& Entity::operator=(const Entity& other)
{
	if (this != &other)
	{
		name = other.name;
		_manager = other._manager;
		_components = other._components;
	}

	return *this;
}

void Entity::Update(float deltaTime)
{
	for(auto& component: _components)
	{
		component->Update(deltaTime);
	}
}

void Entity::Render()
{
	for (auto& component : _components)
	{
		component->Render();
	}
}

void Entity::Destroy()
{
	_isActive = false;
}
