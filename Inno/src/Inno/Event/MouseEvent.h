#pragma once

#include "Event.h"

namespace Inno
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return sstream.str();
		}

		DEFINE_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)
		DEFINE_EVENT_TYPE(MouseMoved)

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			:m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return sstream.str();
		}

		DEFINE_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)
		DEFINE_EVENT_TYPE(MouseScrolled)

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		DEFINE_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		int m_Button;

		MouseButtonEvent(int button)
			: m_Button(button) {}
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "MouseButtonPressedEvent: " << m_Button;
			return sstream.str();
		}

		DEFINE_EVENT_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "MouseButtonReleasedEvent: " << m_Button;
			return sstream.str();
		}

		DEFINE_EVENT_TYPE(MouseButtonReleased)
	};
}
