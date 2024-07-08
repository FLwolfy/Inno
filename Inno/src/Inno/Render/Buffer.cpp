#include "pch.h"
#include "Buffer.h"

#include "Inno/Core/Core.h"
#include "Inno/Render/Renderer.h"

#include "RenderAPI/OpenGL/OpenGLBuffer.h"

namespace Inno
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
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
				return std::make_shared<OpenGLVertexBuffer>(vertices, size);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
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
				return std::make_shared<OpenGLIndexBuffer>(indices, count);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}
}
