#include "pch.h"
#include "VertexArray.h"

#include "Inno/Render/Renderer.h"

#include "RenderAPI/OpenGL/OpenGLVertexArray.h"

namespace Inno
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "RendererAPI::None current not supported!");
				return nullptr;
			}
			case RendererAPI::OpenGL:
			{
				return std::make_shared<OpenGLVertexArray>();
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}
}