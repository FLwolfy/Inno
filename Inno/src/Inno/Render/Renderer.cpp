#include "pch.h"
#include "Renderer.h"

namespace Inno
{
	////////////////* The Renderer Lies Here *////////////////
	std::shared_ptr<RendererAPI> Renderer::s_RendererAPI = nullptr;
	Renderer::SceneData* Renderer::s_SceneData = new SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		s_RendererAPI->DrawIndexed(vertexArray);
	}

	////////////////* The Renderer Command Lies Here *////////////////

	void Renderer::Command::SetAPI(RendererAPI::API api)
	{
		RendererAPI::SetAPI(api);
		s_RendererAPI = RendererAPI::Create();
	}
}