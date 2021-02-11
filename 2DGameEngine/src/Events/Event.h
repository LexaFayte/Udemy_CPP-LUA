#pragma once
#include <functional>
#include <string>
#include "../Helpers.h"

namespace Events
{
	enum class EventType
	{
		None = 0,
		KeyPressed, KeyReleased, KeyHold,

		NUM_EVENT_TYPES
	};

	enum EventCategory
	{
		None = 0,
		Input = BIT(0),
		Keyboard = BIT(1),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; } 

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return (GetCategoryFlags() & category) > 0 ? true : false;
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) :
			_event(e)
		{
		}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (_event.GetEventType() == T::GetStaticType())
			{
				_event.Handled |= func(static_cast<T&>(_event));
				return true;
			}

			return false;
		}

	private:
		Event& _event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}