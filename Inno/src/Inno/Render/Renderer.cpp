#include "pch.h"
#include "Renderer.h"

namespace Inno
{
	Unq<RendererAPI> Renderer::s_RendererAPI = nullptr;
	Unq<Renderer::SceneData> Renderer::s_SceneData = CreateUnq<Renderer::SceneData>();
	ShaderLibrary Renderer::s_ShaderLibrary = ShaderLibrary();

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		shader->Bind();
		shader->SetUniformMat4("u_CameraVP", s_SceneData->ViewProjectionMatrix);
		shader->SetUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		s_RendererAPI->DrawIndexed(vertexArray);
	}
}