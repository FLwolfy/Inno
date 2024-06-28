#pragma once

#include "Inno/Core/Core.h"

namespace Inno
{
	/*
	Events in Inno are currently blocking, which means whenever a event occurs, it immediately get
	dispatched and must be dealt with right away. No buffer queues for events currently.
	*/

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,
		EventCategoryMouseButton = 1 << 4
	};

	/// <summary>
	/// Base class for all events in the Inno engine.
	/// </summary>
	class Event
	{
		GENERIC_TYPE(T, Event)
		using EventFunc = std::function<bool(T&)>;

	public:
		/// <summary>
		/// Flag indicating whether the event has been handled.
		/// </summary>
		bool IsHandled = false;

	public:
		/// <summary>
		/// Retrieves the type of the event.
		/// </summary>
		/// <returns>Type of the event as an EventType enum value.</returns>
		virtual EventType GetEventType() const = 0;

		/// <summary>
		/// Retrieves the name of the event.
		/// </summary>
		/// <returns>Name of the event as a C-string.</returns>
		virtual const char* GetName() const = 0;

		/// <summary>
		/// Retrieves the category flags of the event.
		/// </summary>
		/// <returns>Category flags of the event.</returns>
		virtual int GetCategoryFlags() const = 0;

		/// <summary>
		/// Converts the event to a string representation (default implementation returns the name).
		/// </summary>
		/// <returns>String representation of the event.</returns>
		virtual std::string ToString() const { return GetName(); }

		/// <summary>
		/// Checks if the event belongs to a specified category.
		/// </summary>
		/// <param name="category">Category to check against.</param>
		/// <returns>True if the event belongs to the specified category, false otherwise.</returns>
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		/// <summary>
		/// Dispatches the event to a handler function. If the event type match the dispatched type T, the handler function will be called.
		/// </summary>
		/// <typeparam name="T">: Type of the event to dispatch.</typeparam>
		/// <param name="func">: Handler function that takes the event as a reference.</param>
		/// <returns>True if the event was dispatched and handled, false otherwise.</returns>
		GENERIC_TYPE(T, Event)
		bool Dispatch(EventFunc<T> func)
		{
			if (GetEventType() == T::GetStaticType())
			{
				IsHandled = func(static_cast<T&>(*this));
				return true;
			}

			return false;
		}

		/// <summary>
		/// Converts the event to a string representation.
		/// </summary>
		/// <returns>String representation of the event.</returns>
		operator std::string() const
		{
			return ToString();
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

	/// <summary>
	/// Macro for defining the static type and getter methods for an event type.
	/// </summary>
	#define DEFINE_EVENT_TYPE(type) \
			static EventType GetStaticType() { return EventType::type; } \
			virtual EventType GetEventType() const override { return GetStaticType(); } \
			virtual const char* GetName() const override { return #type; }

	/// <summary>
	/// Macro for defining the category flags getter method for an event.
	/// </summary>
	#define DEFINE_EVENT_CATEGORY(category) \
			virtual int GetCategoryFlags() const override { return category; }
}

