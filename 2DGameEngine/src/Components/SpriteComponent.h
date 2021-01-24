#pragma once
#include <SDL.h>
#include <string>
#include <map>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Component.h"

class TransformComponent;
class Animation;

class SpriteComponent : public Component
{
	// FUNCTIONS
public:
	SpriteComponent() = default;
	SpriteComponent(std::string filePath);
	SpriteComponent(std::string filePath, int numFrames, int animationSpeed, bool hasDirections, bool isFixed);
	SpriteComponent(SDL_Texture* texture, int numFrames, int animationSpeed, bool hasDirections, bool isFixed);
	~SpriteComponent();

	// copy constructor
	SpriteComponent(const SpriteComponent& other);

	// move constructor
	SpriteComponent(SpriteComponent&& other) noexcept;


	// copy assignment
	SpriteComponent& operator=(const SpriteComponent& other);

	// move assignment
	SpriteComponent& operator=(SpriteComponent&& other);

	void SetTexture(std::string assetTextureId);

	void Initialize(Entity* owner) override;
	void Update(float deltaTime) override;
	void Render() override;

	void PlayAnimation(std::string animName);

private:

	// VARS
public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
private:
	TransformComponent* _transform = nullptr;
	SDL_Texture* _texture = nullptr;
	SDL_Rect source;
	SDL_Rect dest;

	// animation information
	bool _isAnimated = false;
	bool _isFixed = false;
	int _numFrames = 0;
	int _animSpeed = 0;

	std::string _currentAnimName;
	int _animIndex = 0;

	//map of animations
	std::map<std::string, Animation> _animations;
};

