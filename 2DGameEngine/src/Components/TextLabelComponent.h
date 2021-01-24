#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "../FontManager.h"
#include "../AssetManager.h"
#include "../EntityManager.h"
#include "../Game.h"
#include "../Component.h"

class TextLabelComponent : public Component
{
	// FUNCTIONS
public:
	TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color) :
		_text(text),
		_fontFamily(fontFamily),
		_color(color)
	{
		_position.x = x;
		_position.y = y;

		SetLabelText(_text, _fontFamily);
	}

private:
	void SetLabelText(std::string text, std::string fontFamily)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(Game::GetAssetManager()->GetFont(fontFamily), text.c_str(), _color);
		_texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(_texture, NULL, NULL, &_position.w, &_position.h);
	}

	void Render() override
	{
		FontManager::Draw(_texture, _position);
	}

	// VARS
public:


private:
	SDL_Rect _position;
	std::string _text;
	std::string _fontFamily;
	SDL_Color _color;
	SDL_Texture* _texture = nullptr;
};

