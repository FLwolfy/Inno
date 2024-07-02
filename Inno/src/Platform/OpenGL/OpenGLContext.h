#pragma once

#include "Inno/Render/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Inno {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}

