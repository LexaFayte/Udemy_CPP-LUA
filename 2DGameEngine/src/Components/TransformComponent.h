#pragma once
#include "../Component.h"
#include "../EntityManager.h"
#include "../libs/glm/glm.hpp"

class TransformComponent : public Component
{
	// FUNCTIONS
public:
	TransformComponent();
	TransformComponent(int PosX, int PosY, int VelX, int VelY, int width, int height, int scale);
	~TransformComponent(){}

	// copy constructor
	TransformComponent(const TransformComponent& other);

	// move constructor
	TransformComponent(TransformComponent&& other) noexcept;

	// copy assignment
	TransformComponent& operator=(const TransformComponent& other);

	// move assignment
	TransformComponent& operator=(TransformComponent&& other) noexcept;

	void Initialize(Entity* owner) override;
	void Update(float deltaTime) override;
	void Render() override;
private:

	// VARS
public:
	glm::vec2 position;
	glm::vec2 velocity;
	int width;
	int height;
	int scale;

private:
};