#include "InputControlComponent.h"
#include "../Entity.h"

//InputControlComponent::InputControlComponent(const InputControlComponent& other)
//{
//
//}
//
//InputControlComponent::InputControlComponent(InputControlComponent&& other)
//{
//
//}
//
//InputControlComponent& InputControlComponent::operator=(const InputControlComponent& other)
//{
//
//}
//
//InputControlComponent& InputControlComponent::operator=(InputControlComponent&& other)
//{
//
//}

void InputControlComponent::Initialize(Entity* owner)
{
	_owner = owner;
}

void InputControlComponent::Update(float deltaTime)
{
	//#TODO_REFACTOR
	if(Game::event.type == SDL_KEYDOWN)
	{
		SDL_Keycode key = Game::event.key.keysym.sym;
		auto* transComp = _owner->GetComponent<TransformComponent>();
		auto* spriteComp = _owner->GetComponent<SpriteComponent>();

		if(key == SDLK_w)//UP
		{
			transComp->velocity.y = -PLAYER_SPEED;
			transComp->velocity.x = 0;
			spriteComp->PlayAnimation("Up");
		}

		else if(key == SDLK_a)//LEFT
		{
			transComp->velocity.y = 0;
			transComp->velocity.x = -PLAYER_SPEED;
			spriteComp->PlayAnimation("Left");
		}

		else if(key == SDLK_s)//DOWN
		{
			transComp->velocity.y = PLAYER_SPEED;
			transComp->velocity.x = 0;
			spriteComp->PlayAnimation("Down");
		}

		else if(key == SDLK_d)//RIGHT
		{
			transComp->velocity.y = 0;
			transComp->velocity.x = PLAYER_SPEED;
			spriteComp->PlayAnimation("Right");
		}

		else if (key == SDLK_RETURN)//SHOOT
		{

		}
	}

	if (Game::event.type == SDL_KEYUP)
	{
		SDL_Keycode key = Game::event.key.keysym.sym;
		TransformComponent* transComp = _owner->GetComponent<TransformComponent>();
		SpriteComponent* spriteComp = _owner->GetComponent<SpriteComponent>();

		if (key == SDLK_w)//UP
		{
			transComp->velocity.y = 0;
			//transComp->velocity.x = 0;
			
		}

		else if (key == SDLK_a)//LEFT
		{
			//transComp->velocity.y = 0;
			transComp->velocity.x = 0;
			
		}

		else if (key == SDLK_s)//DOWN
		{
			transComp->velocity.y = 0;
			//transComp->velocity.x = 0;
			
		}

		else if (key == SDLK_d)//RIGHT
		{
			//transComp->velocity.y = 0;
			transComp->velocity.x = 0;
			
		}

		else if (key == SDLK_RETURN)//SHOOT
		{
			// No Shooty
		}
	}
}

void InputControlComponent::Render()
{
	
}
