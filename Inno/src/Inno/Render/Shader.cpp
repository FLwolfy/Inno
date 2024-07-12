#include "pch.h"
#include "Shader.h"

#include "Inno/Render/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLShader.h"

namespace Inno
{
	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
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
				return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}
}