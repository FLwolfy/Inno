#include "pch.h"
#include "VertexArray.h"

#include "Inno/Render/Renderer.h"

#include "RenderAPI/OpenGL/OpenGLVertexArray.h"

namespace Inno
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::Command::GetAPI())
		{
			case RendererAPI::API::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "RendererAPI::None current not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLVertexArray>();
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}
}