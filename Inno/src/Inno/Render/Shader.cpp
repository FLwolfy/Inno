#include "pch.h"
#include "Shader.h"

#include "Inno/Render/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLShader.h"

namespace Inno
{
	////////////////////* Shader *////////////////////

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "RendererAPI::None current not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}

	Ref<Shader> Shader::Create(const std::string& filepath, const std::string& name)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "RendererAPI::None current not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLShader>(filepath, name);
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}

	////////////////////* Shader Library *////////////////////

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		INNO_CORE_ASSERT(!Contains(name), "Shader already exists!");
		m_ShaderContainer[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath, const std::string& name)
	{
		auto shader = Shader::Create(filepath, name);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		INNO_CORE_ASSERT(Contains(name), "Shader not found!");
		return m_ShaderContainer[name];
	}

	bool ShaderLibrary::Contains(const std::string& name) const
	{
		return m_ShaderContainer.find(name) != m_ShaderContainer.end();
	}
}