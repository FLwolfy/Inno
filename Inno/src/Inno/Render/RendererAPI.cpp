#include "pch.h"
#include "RendererAPI.h"

#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

namespace Inno
{
	/* Set to None as default */
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;

	std::shared_ptr<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "RendererAPI::None current not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLRendererAPI>();
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI");
				return nullptr;
			}
		}
	}
}
