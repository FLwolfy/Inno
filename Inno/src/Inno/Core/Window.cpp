#include "pch.h"
#include "Window.h"

#include "Inno/Core/Log.h"
#include "Inno/Core/Core.h"
#include "Inno/Event/ApplicationEvent.h"
#include "Inno/Event/KeyEvent.h"
#include "Inno/Event/MouseEvent.h"

#include <glad/glad.h>

namespace Inno
{
	static unsigned int s_GLFWWindowCount = 0;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new Window(properties);
	}

	Window::Window(const WindowProperties& properties)
	{
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		INNO_CORE_LOGTRACE("Creating Window {0} ({1}, {2}) in Windows System", properties.Title, properties.Width, properties.Height);

		// Initialize GLFW
		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			INNO_CORE_ASSERT(success, "Initializing GLFW failed!");
		}

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		INNO_CORE_ASSERT(success, "Initializing GLAD failed!")

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

		if (s_GLFWWindowCount == 0)
		{
			glfwSetErrorCallback([](int error, const char* description)
			{
				INNO_CORE_LOGERROR("GLFW Error ({0}): {1}", error, description);
			});
		}

		// Increase GLFW Window Counter
		s_GLFWWindowCount++;
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		s_GLFWWindowCount--;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(bool enabled)
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

	bool Window::IsVSync() const
	{
		return m_Data.VSync;
	}
}