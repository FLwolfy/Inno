#pragma once

#include "Event.h"
#include "Inno/Core/Keycode.h"

namespace Inno
{
	class KeyEvent : public Event
	{
	public:
		inline unsigned int GetKeyCode() const { return m_Keycode; }

		DEFINE_EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		unsigned int m_Keycode;

		KeyEvent(unsigned int keycode)
			: m_Keycode(keycode) {}
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(unsigned int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "KeyPressedEvent: " << m_Keycode << " (" << m_RepeatCount << " repeats)";
			return sstream.str();
		}

		DEFINE_EVENT_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(unsigned int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "KeyReleaseEvent: " << m_Keycode;
			return sstream.str();
		}

		DEFINE_EVENT_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(unsigned int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "KeyTypedEvent: " << m_Keycode;
			return sstream.str();
		}

		DEFINE_EVENT_TYPE(KeyTyped)
	};
}
