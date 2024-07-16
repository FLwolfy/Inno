#pragma once

#include "Inno/Core/Core.h"

namespace Inno
{
    /**
     * Events in Inno are currently blocking, which means whenever an event occurs, it immediately gets dispatched and must be dealt with right away. No buffer queues for events currently.
     */

    /**
     * @brief Enum defining different types of events supported by Inno.
     */
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    /**
     * @brief Enum defining different categories of events.
     */
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = 1 << 0,
        EventCategoryInput = 1 << 1,
        EventCategoryKeyboard = 1 << 2,
        EventCategoryMouse = 1 << 3,
        EventCategoryMouseButton = 1 << 4
    };

    /**
     * @brief Base class for all events in the Inno engine.
     */
    class Event : public ILoggable
    {
        GENERIC_TYPE(T, Event)
        using EventFunc = std::function<bool(T&)>;

    public:
        /**
         * @brief Flag indicating whether the event has been handled.
         */
        bool IsHandled = false;

    public:
        /**
         * @brief Retrieves the type of the event.
         * @return Type of the event as an EventType enum value.
         */
        virtual EventType GetEventType() const = 0;
        /**
         * @brief Retrieves the name of the event.
         * @return Name of the event as a C-string.
         */
        virtual const char* GetName() const = 0;
        /**
         * @brief Retrieves the category flags of the event.
         * @return Category flags of the event.
         */
        virtual int GetCategoryFlags() const = 0;

        /**
         * @brief Checks if the event belongs to a specified category.
         * @param category Category to check against.
         * @return True if the event belongs to the specified category, false otherwise.
         */
        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

        /**
         * @brief Dispatches the event to a handler function.
         * If the event type matches the dispatched type T, the handler function will be called.
         * @tparam T Type of the event to dispatch.
         * @param func Handler function that takes the event as a reference.
         * @return True if the event was dispatched and handled, false otherwise.
         */
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

        /**
         * @brief Converts the event to a string representation (default implementation returns the name).
         * @return String representation of the event.
         */
        virtual std::string ToString() const override { return GetName(); }
    };

    /**
     * @brief Macro for defining the static type and getter methods for an event type.
     * @param type Type of the event.
     */
    #define DEFINE_EVENT_TYPE(type) \
            static EventType GetStaticType() { return EventType::type; } \
            virtual EventType GetEventType() const override { return GetStaticType(); } \
            virtual const char* GetName() const override { return #type; }

    /**
     * @brief Macro for defining the category flags getter method for an event.
     * @param category Category flags for the event.
     */
    #define DEFINE_EVENT_CATEGORY(category) \
            virtual int GetCategoryFlags() const override { return category; }
}
