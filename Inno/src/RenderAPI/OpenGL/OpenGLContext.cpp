#include "pch.h"
#include "OpenGLContext.h"

#include "RenderAPI/OpenGL/OpenGLContext.h"
#include "Inno/Core/Core.h"

#include <glad/glad.h>

namespace Inno {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		INNO_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		INNO_CORE_ASSERT(status, "Failed to initialize Glad!");

		// INNO_CORE_LOGINFO("OpenGL Renderer:\n    [Vendor]: {0}\n    [Renderer]: {1}\n    [Version]: {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
