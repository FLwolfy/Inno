#pragma once

#include "Event.h"

namespace Inno {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream sstream;
			sstream << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return sstream.str();
		}

		DEFINE_EVENT_TYPE(WindowResize)
		DEFINE_EVENT_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		DEFINE_EVENT_TYPE(WindowClose)
		DEFINE_EVENT_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		DEFINE_EVENT_TYPE(AppTick)
		DEFINE_EVENT_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		DEFINE_EVENT_TYPE(AppUpdate)
		DEFINE_EVENT_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		DEFINE_EVENT_TYPE(AppRender)
		DEFINE_EVENT_CATEGORY(EventCategoryApplication)
	};
}