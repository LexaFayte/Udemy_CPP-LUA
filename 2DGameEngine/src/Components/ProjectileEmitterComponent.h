#pragma once
#include "../Component.h"
#include "../../libs/glm/glm.hpp"
#include "../EntityManager.h"
#include "TransformComponent.h"

class ProjectileEmitterComponent : public Component
{
	// FUNCTIONS
public:
	ProjectileEmitterComponent(int speed, int angleInDegs, int range, bool loopFiring = false) :
		_speed(speed),
		_angleRads(glm::radians(static_cast<float>(angleInDegs))),
		_range(range),
		_loopFiring(loopFiring)
	{

	}

	


	void Initialize(Entity* owner) override
	{
		_owner = owner;

		if(_transformComponent = _owner->GetComponent<TransformComponent>())
		{
			_origin = glm::vec2(_transformComponent->position.x, _transformComponent->position.y);
			_transformComponent->velocity = glm::vec2(glm::cos(_angleRads)*_speed, glm::sin(_angleRads)*_speed);
		}
	}


	void Update(float deltaTime) override
	{
		if(_transformComponent && glm::distance(_transformComponent->position, _origin) > _range)
		{
			if (_loopFiring)
			{
				_transformComponent->position = _origin;
			}
			else
			{
				_owner->Destroy();
			}			
		}
	}

private:


	
	// VARS
public:


private:
	TransformComponent* _transformComponent = nullptr;
	glm::vec2 _origin;
	int _speed = 0;
	int _range = 0;
	float _angleRads = 0; // in radians
	bool _loopFiring = false;

};