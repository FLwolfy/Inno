#include "pch.h"
#include "Window.h"

#include "RenderAPI/OpenGL/OpenGLWindow.h"

namespace Inno
{
	/* Set to None as default */
	Window::API Window::s_WindowAPI = Window::API::None;

	Window::Window(const WindowProperties& properties)
	{
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		INNO_CORE_LOGTRACE("Creating Window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);
	}

	Window* Window::Create(const WindowProperties& properties)
	{
		switch (s_WindowAPI)
		{
			case Window::API::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "Window::API::None current not supported!");
				return nullptr;
			}
			case Window::API::OpenGL:
			{
				return new OpenGLWindow();
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}
}
