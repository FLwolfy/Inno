#include "pch.h"
#include "Renderer.h"

namespace Inno
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		s_RendererAPI->DrawIndexed(vertexArray);
	}

	/* The Renderer Command Lies Here */
	void Renderer::Command::SetAPI(RendererAPI::API api)
	{
		RendererAPI::SetAPI(api);
		s_RendererAPI = RendererAPI::Create();
	}
}