#include "pch.h"
#include "OpenGLWindow.h"

#include "Inno/Event/ApplicationEvent.h"
#include "Inno/Event/KeyEvent.h"
#include "Inno/Event/MouseEvent.h"

#include "RenderAPI/OpenGL/OpenGLContext.h"

namespace Inno
{
	unsigned int OpenGLWindow::s_GLFWWindowCount = 0;

	OpenGLWindow::OpenGLWindow(const WindowProperties& properties)
		: Window(properties)
	{
		// Initialize GLFW
		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			INNO_CORE_ASSERT(success, "Initializing GLFW failed!");
		}

		GLFWwindow* glfwWindow = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_WindowHandle = glfwWindow;
		m_Context = new OpenGLContext(glfwWindow);
		m_Context->Init();

		glfwSetWindowUserPointer(glfwWindow, &m_Data);
		SetVSync(true);

		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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

		glfwSetCharCallback(glfwWindow, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods)
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

		glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double xPos, double yPos)
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

	OpenGLWindow::~OpenGLWindow()
	{
		glfwDestroyWindow((GLFWwindow*)m_WindowHandle);
		delete m_Context;
		s_GLFWWindowCount--;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void OpenGLWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void OpenGLWindow::SetVSync(bool enabled)
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

	bool OpenGLWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}