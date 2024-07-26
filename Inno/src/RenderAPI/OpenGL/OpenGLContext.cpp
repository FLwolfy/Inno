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

		INNO_CORE_LOGINFO("The Renderer Context Info:");
		INNO_CORE_LOGINFO("+-------------------------------------------------------------------------+");
		INNO_CORE_LOGINFO("|                               OpenGL Info                               |");
		INNO_CORE_LOGINFO("+-------------------------------------------------------------------------+");
		INNO_CORE_LOGINFO("| Vendor   : {:<60} |", (const char*)glGetString(GL_VENDOR));
		INNO_CORE_LOGINFO("| Renderer : {:<60} |", (const char*)glGetString(GL_RENDERER));
		INNO_CORE_LOGINFO("| Version  : {:<60} |", (const char*)glGetString(GL_VERSION));
		INNO_CORE_LOGINFO("+-------------------------------------------------------------------------+");

		INNO_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Inno Engine requires OpenGL version >= 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
