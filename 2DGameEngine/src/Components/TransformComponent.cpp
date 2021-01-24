#include "TransformComponent.h"
#include "../Entity.h"
#include "../Game.h"
#include <SDL.h>

// ======================================================================================================
// #TRANSFORM_COMPONENET_CONSTRCUTORS
// ======================================================================================================

TransformComponent::TransformComponent() :
	position(glm::vec2(0, 0)),
	velocity(glm::vec2(0, 0)),
	width(32),
	height(32),
	scale(1)
{

}

TransformComponent::TransformComponent(int PosX, int PosY, int VelX, int VelY, int width, int height, int scale) :
	position(glm::vec2(PosX, PosY)),
	velocity(glm::vec2(VelX, VelY)),
	width(width),
	height(height),
	scale(scale)
{

}

TransformComponent::TransformComponent(const TransformComponent& other) :
	position(other.position),
	velocity(other.velocity),
	width(other.width),
	height(other.height),
	scale(other.scale)
{

}

TransformComponent::TransformComponent(TransformComponent&& other) noexcept :
	position(std::exchange(other.position, glm::vec2(0,0))),
	velocity(std::exchange(other.velocity, glm::vec2(0,0))),
	width(std::exchange(other.width,0)),
	height(std::exchange(other.height,0)),
	scale(std::exchange(other.scale,0))
{

}


TransformComponent& TransformComponent::operator=(const TransformComponent& other)
{
	if (this != &other)
	{
		position = other.position;
		velocity = other.velocity;
		width = other.width;
		height = other.height;
		scale = other.scale;
	}

	return *this;
}

TransformComponent& TransformComponent::operator=(TransformComponent&& other) noexcept
{
	if(this != &other)
	{
		position = std::exchange(other.position, glm::vec2(0, 0));
		velocity = std::exchange(other.velocity, glm::vec2(0, 0));
		width = std::exchange(other.width, 0);
		height = std::exchange(other.height, 0);
		scale = std::exchange(other.scale, 0);
	}

	return *this;
}

// ======================================================================================================
// #TRANSFORM_COMPONENET_FUNCTIONS
// ======================================================================================================

void TransformComponent::Initialize(Entity* owner)

{
	_owner = owner;
}

void TransformComponent::Update(float deltaTime)
{
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
}

void TransformComponent::Render()
{

}
