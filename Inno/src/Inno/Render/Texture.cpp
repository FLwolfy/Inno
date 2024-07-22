#include "pch.h"
#include "Texture.h"

#include "Inno/Render/Renderer.h"

#include "RenderAPI/OpenGL/OpenGLTexure.h"

namespace Inno
{
	Ref<Texture2D> Texture2D::Create(const TextureProperties& properties)
	{
		switch (Renderer::Command::GetAPI())
		{
			case RendererAPI::API::None:
			{
				INNO_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLTexture2D>(properties);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::Command::GetAPI())
		{
			case RendererAPI::API::None:
			{
				INNO_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLTexture2D>(path);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}
}