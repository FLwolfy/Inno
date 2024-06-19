#include "pch.h"
#include "Window.h"

#include "Inno/Core/Log.h"
#include "Inno/Core/Core.h"

namespace Inno
{
	#ifdef INNO_PLATFORM_WINDOWS

	static unsigned int s_GLFWWindowCount = 0;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		INNO_CORE_LOGINFO("Creating Window {0} ({1}, {2}) in Windows System", properties.Title, properties.Width, properties.Height);

		// Initialize GLFW only once
		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			INNO_CORE_ASSERT(success, "Initializing GLFW failed!");
		}
		s_GLFWWindowCount++;

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		s_GLFWWindowCount--;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	#endif
}