#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "../Game.h"
#include "../Entity.h"
#include "../Animation.h"

// ======================================================================================================
// #SPRITE_COMPONENET_CONSTRCUTORS
// ======================================================================================================

SpriteComponent::SpriteComponent(std::string filePath)
{
	SetTexture(filePath);
}

SpriteComponent::SpriteComponent(std::string filePath, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) :
	_numFrames(numFrames),
	_animSpeed(animationSpeed),
	_isFixed(isFixed)
{
	_isAnimated = true;
	
	if(hasDirections)
	{
		_animations.emplace("Down", Animation(0, _numFrames, _animSpeed));
		_animations.emplace("Right", Animation(1, _numFrames, _animSpeed));
		_animations.emplace("Left", Animation(2, _numFrames, _animSpeed));
		_animations.emplace("Up", Animation(3, _numFrames, _animSpeed));

		_animIndex = 0;
		_currentAnimName = "Down";
	}
	else
	{
		_animIndex = 0;
		_currentAnimName = "SingleAnim";
		_animations.emplace(_currentAnimName, Animation(0, _numFrames, _animSpeed));
	}
	
	SetTexture(filePath);

	PlayAnimation(_currentAnimName);
}

SpriteComponent::SpriteComponent(SDL_Texture* texture, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) :
	_numFrames(numFrames),
	_animSpeed(animationSpeed),
	_isFixed(isFixed),
	_texture(texture)
{
	_isAnimated = true;

	if (hasDirections)
	{
		_animations.emplace("Down", Animation(0, _numFrames, _animSpeed));
		_animations.emplace("Right", Animation(1, _numFrames, _animSpeed));
		_animations.emplace("Left", Animation(2, _numFrames, _animSpeed));
		_animations.emplace("Up", Animation(3, _numFrames, _animSpeed));

		_animIndex = 0;
		_currentAnimName = "Down";
	}
	else
	{
		_animIndex = 0;
		_currentAnimName = "SingleAnim";
		_animations.emplace(_currentAnimName, Animation(0, _numFrames, _animSpeed));
	}

	PlayAnimation(_currentAnimName);
}

SpriteComponent::~SpriteComponent()
{

}

SpriteComponent::SpriteComponent(const SpriteComponent& other) :
	_texture(other._texture),
	source(other.source),
	dest(other.dest)
{
	_transform = _owner->GetComponent<TransformComponent>();
}

SpriteComponent::SpriteComponent(SpriteComponent&& other) noexcept :
	_texture(std::exchange(other._texture, nullptr)),
	_transform(std::exchange(other._transform, nullptr)),
	source(other.source),
	dest(other.dest)
{
	
}


SpriteComponent& SpriteComponent::operator=(const SpriteComponent& other)
{
	if(this != &other)
	{
		_texture = other._texture;
		_transform = _owner->GetComponent<TransformComponent>();
		source = other.source;
		dest = other.dest;
	}

	return *this;
}

SpriteComponent& SpriteComponent::operator=(SpriteComponent&& other)
{
	if(this != &other)
	{
		_texture = std::exchange(other._texture, nullptr);
		_transform = std::exchange(other._transform, nullptr);
		source = other.source;
		dest = other.dest;
	}

	return *this;
}

// ======================================================================================================
// #SPRITE_COMPONENET_FUNCTIONS
// ======================================================================================================

void SpriteComponent::SetTexture(std::string assetTextureId)
{
	_texture = Game::GetAssetManager()->GetTexture(assetTextureId);
}

void SpriteComponent::Initialize(Entity* owner)
{
	if(_owner = owner; _owner != nullptr)
	{
		_transform = _owner->GetComponent<TransformComponent>();
		source.x = 0;
		source.y = 0;
		source.w = _transform->width;
		source.h = _transform->height;
	}
}

void SpriteComponent::Update(float deltaTime)
{
	if (_transform)
	{
		if(_isAnimated)
		{
			source.x = source.w * static_cast<int>((SDL_GetTicks() / _animSpeed) % _numFrames);
		}
		
		source.y = _animIndex * _transform->height;

		dest.x = static_cast<int>(_transform->position.x) - (_isFixed ? 0 : Game::camera.x);
		dest.y = static_cast<int>(_transform->position.y) - (_isFixed ? 0 : Game::camera.y);
		dest.w = _transform->width * _transform->scale;
		dest.h = _transform->height * _transform->scale;
	}
}

void SpriteComponent::Render()
{
	TextureManager::Draw(_texture, source, dest, spriteFlip);
}

void SpriteComponent::PlayAnimation(std::string animName)
{
	_numFrames = _animations[animName].numFrames;
	_animIndex = _animations[animName].index;
	_animSpeed = _animations[animName].animationSpeed;
	_currentAnimName = animName;
}
