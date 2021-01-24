#include "Component.h"
#include "Entity.h"

Component::Component(const Component& other)
{
	_owner = new Entity(*other._owner);
}

Component::Component(Component&& other) noexcept : _owner(std::exchange(other._owner, nullptr))
{

}

Component& Component::operator=(Component&& other)
{
	if (this != &other)
	{
		_owner = std::exchange(other._owner, nullptr);
	}

	return *this;
}

Component& Component::operator=(const Component& other)
{
	if (this != &other)
	{
		_owner = new Entity(*other._owner);
	}

	return *this;
}

void Component::Initialize(Entity* owner)
{
	_owner = owner;
}

void Component::Update(float deltaTime)
{

}

void Component::Render()
{

}
