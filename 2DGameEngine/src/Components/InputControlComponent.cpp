#include "InputControlComponent.h"
#include "../Entity.h"
#include "../Events/KeyEvent.h"

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

int SDLCALL KeyEventsWatch(void* data, SDL_Event* e)
{

	if (e->type == SDL_EventType::SDL_KEYDOWN)
	{
		Events::KeyPressedEvent keyPressedE(*e);
		std::cout << keyPressedE.ToString();
		//OnKeyDown(e->key.keysym.sym);
	}

	if (e->type == SDL_EventType::SDL_KEYUP)
	{
		Events::KeyReleasedEvent keyReleasedE(*e);
		std::cout << keyReleasedE.ToString();
	}

	return 0;
}

void InputControlComponent::Initialize(Entity* owner)
{
	_owner = owner;	
	SDL_AddEventWatch(KeyEventsWatch, this);
}

void InputControlComponent::Update(float deltaTime)
{
	//#TODO_REFACTOR
	//if(Game::event.type == SDL_KEYDOWN)
	//{
	//	SDL_Keycode key = Game::event.key.keysym.sym;
	//	auto* transComp = _owner->GetComponent<TransformComponent>();
	//	auto* spriteComp = _owner->GetComponent<SpriteComponent>();

	//	if(key == SDLK_w)//UP
	//	{
	//		transComp->velocity.y = -PLAYER_SPEED;
	//		transComp->velocity.x = 0;
	//		spriteComp->PlayAnimation("Up");
	//	}

	//	else if(key == SDLK_a)//LEFT
	//	{
	//		transComp->velocity.y = 0;
	//		transComp->velocity.x = -PLAYER_SPEED;
	//		spriteComp->PlayAnimation("Left");
	//	}

	//	else if(key == SDLK_s)//DOWN
	//	{
	//		transComp->velocity.y = PLAYER_SPEED;
	//		transComp->velocity.x = 0;
	//		spriteComp->PlayAnimation("Down");
	//	}

	//	else if(key == SDLK_d)//RIGHT
	//	{
	//		transComp->velocity.y = 0;
	//		transComp->velocity.x = PLAYER_SPEED;
	//		spriteComp->PlayAnimation("Right");
	//	}

	//	else if (key == SDLK_RETURN)//SHOOT
	//	{

	//	}
	//}

	//if (Game::event.type == SDL_KEYUP)
	//{
	//	SDL_Keycode key = Game::event.key.keysym.sym;
	//	TransformComponent* transComp = _owner->GetComponent<TransformComponent>();
	//	SpriteComponent* spriteComp = _owner->GetComponent<SpriteComponent>();

	//	if (key == SDLK_w)//UP
	//	{
	//		transComp->velocity.y = 0;
	//		//transComp->velocity.x = 0;
	//		
	//	}

	//	else if (key == SDLK_a)//LEFT
	//	{
	//		//transComp->velocity.y = 0;
	//		transComp->velocity.x = 0;
	//		
	//	}

	//	else if (key == SDLK_s)//DOWN
	//	{
	//		transComp->velocity.y = 0;
	//		//transComp->velocity.x = 0;
	//		
	//	}

	//	else if (key == SDLK_d)//RIGHT
	//	{
	//		//transComp->velocity.y = 0;
	//		transComp->velocity.x = 0;
	//		
	//	}

	//	else if (key == SDLK_RETURN)//SHOOT
	//	{
	//		// No Shooty
	//	}
	//}
}

void InputControlComponent::Render()
{
	
}

void InputControlComponent::OnKeyDown(SDL_Keycode keycode)
{
	auto* transComp = _owner->GetComponent<TransformComponent>();
	auto* spriteComp = _owner->GetComponent<SpriteComponent>();

	if (keycode == SDLK_w)//UP
	{
		transComp->velocity.y = -PLAYER_SPEED;
		transComp->velocity.x = 0;
		spriteComp->PlayAnimation("Up");
	}

	else if (keycode == SDLK_a)//LEFT
	{
		transComp->velocity.y = 0;
		transComp->velocity.x = -PLAYER_SPEED;
		spriteComp->PlayAnimation("Left");
	}

	else if (keycode == SDLK_s)//DOWN
	{
		transComp->velocity.y = PLAYER_SPEED;
		transComp->velocity.x = 0;
		spriteComp->PlayAnimation("Down");
	}

	else if (keycode == SDLK_d)//RIGHT
	{
		transComp->velocity.y = 0;
		transComp->velocity.x = PLAYER_SPEED;
		spriteComp->PlayAnimation("Right");
	}

	else if (keycode == SDLK_RETURN)//SHOOT
	{

	}
}

void InputControlComponent::OnKeyUp(SDL_Keycode keycode)
{
	auto* transComp = _owner->GetComponent<TransformComponent>();
	auto* spriteComp = _owner->GetComponent<SpriteComponent>();

	if (keycode == SDLK_w)//UP
	{
		transComp->velocity.y = 0;
		//transComp->velocity.x = 0;

	}

	else if (keycode == SDLK_a)//LEFT
	{
		//transComp->velocity.y = 0;
		transComp->velocity.x = 0;

	}

	else if (keycode == SDLK_s)//DOWN
	{
		transComp->velocity.y = 0;
		//transComp->velocity.x = 0;

	}

	else if (keycode == SDLK_d)//RIGHT
	{
		//transComp->velocity.y = 0;
		transComp->velocity.x = 0;

	}

	else if (keycode == SDLK_RETURN)//SHOOT
	{
		// No Shooty
	}
}

