#pragma once

#include "Inno/Render/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Inno {

	/// <summary>
	/// OpenGL-specific implementation of the GraphicsContext.
	/// Manages the OpenGL rendering context and buffer swapping.
	/// </summary>
	class OpenGLContext : public GraphicsContext
	{
	public:
		/// <summary>
		/// Constructs an OpenGLContext with a specified GLFW window handle.
		/// </summary>
		/// <param name="windowHandle">The handle to the GLFW window.</param>
		OpenGLContext(GLFWwindow* windowHandle);

		/// <summary>
		/// Initializes the OpenGL context and sets up the necessary OpenGL state and configurations.
		/// </summary>
		virtual void Init() override;
		/// <summary>
		/// Swaps the front and back buffers of the OpenGL context. Presents the rendered frame to the screen.
		/// </summary>
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

