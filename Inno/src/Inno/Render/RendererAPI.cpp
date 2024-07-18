#include "pch.h"
#include "RendererAPI.h"

#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

namespace Inno
{
	/* Set to None as default */
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;

	Unq<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "RendererAPI::API::None current not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateUnq<OpenGLRendererAPI>();
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI");
				return nullptr;
			}
		}
	}
}
