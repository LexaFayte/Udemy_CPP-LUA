#pragma once

#include "Event.h"
#include <SDL_events.h>
#include "../Game.h"

namespace Events
{

	class KeyEvent : Event
	{
	public:
		SDL_Event GetKeyboardEvent() const { return _event; }
		SDL_Keycode GetKeyCode() const { return _event.key.keysym.sym; }

		EVENT_CLASS_CATEGORY(Input | Keyboard);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Event: " << _event.key.keysym.sym << std::endl;
			return ss.str();
		}

	protected:
		KeyEvent(const SDL_Event keyboardEvent) :
			_event(keyboardEvent)
		{}

		SDL_Event _event;
	};

	// Key Pressed (Key Down)
	class KeyPressedEvent : KeyEvent
	{
	public:
		KeyPressedEvent(const SDL_Event keyboardEvent) :
		KeyEvent(keyboardEvent)
		{
			// experimental
			Game::GetEntityManager().InputReceived(keyboardEvent, true);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed: " << _event.key.keysym.sym << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	};

	// Key Released (Key Up)
	class KeyReleasedEvent : KeyEvent
	{
	public:
		KeyReleasedEvent(const SDL_Event keyboardEvent) :
			KeyEvent(keyboardEvent)
		{
			// experimental
			Game::GetEntityManager().InputReceived(keyboardEvent, false);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Released: " << _event.key.keysym.sym << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};
}