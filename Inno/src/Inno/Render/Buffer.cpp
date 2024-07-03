#include "pch.h"
#include "Buffer.h"

#include "Inno/Core/Core.h"
#include "Inno/Render/Renderer.h"

#include "RenderAPI/OpenGL/OpenGLBuffer.h"

namespace Inno
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
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
				return new OpenGLVertexBuffer(vertices, size);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
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
				return new OpenGLIndexBuffer(indices, count);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}
}
