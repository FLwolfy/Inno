#include "pch.h"
#include "GraphicsContext.h"

#include "RenderAPI/OpenGL/OpenGLContext.h"

namespace Inno
{
	/* Set to None as default */
	RendererAPI::API GraphicsContext::s_ContextAPI = RendererAPI::API::None;

	GraphicsContext* GraphicsContext::Create(void* windowHandle)
	{
		switch (s_ContextAPI)
		{
			case RendererAPI::API::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "RendererAPI::None current not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLContext((GLFWwindow*)windowHandle);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}
}