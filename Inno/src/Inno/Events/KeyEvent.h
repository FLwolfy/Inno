#pragma once

#include "Event.h"

namespace Inno
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		DEFINE_EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		int m_KeyCode;

		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return sstream.str();
		}

		DEFINE_EVENT_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "KeyReleaseEvent: " << m_KeyCode;
			return sstream.str();
		}

		DEFINE_EVENT_TYPE(KeyReleased)
	};
}
