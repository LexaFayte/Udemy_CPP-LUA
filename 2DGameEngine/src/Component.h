#pragma once
#include <memory>

class Entity;

class Component
{
	// FUNCTIONS
public:
	Component(){};
	
	virtual ~Component() { _owner = nullptr; };

	// copy constructor
	Component(const Component& other);

	// move constructor
	Component(Component&& other) noexcept;


	// copy assignment
	Component& operator=(const Component& other);

	// move assignment
	Component& operator=(Component&& other);

	virtual void Initialize(Entity* owner);
	virtual void Update(float deltaTime);
	virtual void Render();

private:

	// VARS
public:

protected:
	Entity* _owner = nullptr;

private:
};