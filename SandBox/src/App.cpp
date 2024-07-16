#include <Inno.h>
#include <Inno/Core/Log.h>

class ExampleLayer : public Inno::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_Camera = Inno::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

		m_TriangleVA = Inno::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Inno::VertexBuffer> triangleVB = Inno::VertexBuffer::Create(vertices, sizeof(vertices));

		Inno::ShaderDataType t = Inno::ShaderDataType::Float;
		triangleVB->SetLayout({
			{ Inno::ShaderDataType::Float3, "a_Position" },
			{ Inno::ShaderDataType::Float4, "a_Color"}
		});

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Inno::IndexBuffer> triangleIB = Inno::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_TriangleVA->AddVertexBuffer(triangleVB);
		m_TriangleVA->SetIndexBuffer(triangleIB);

		std::string shaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string shaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				o_Color = v_Color;
			}
		)";

		m_TriangleShader = Inno::Shader::Create("Triangle Shader", shaderVertexSrc, shaderFragmentSrc);
	}

	virtual void OnUpdate() override
	{
		Inno::Renderer::Command::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Inno::Renderer::Command::Clear();

		m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
		m_Camera.SetRotation({ 0.0f, 0.0f, 45.0f });

		Inno::Renderer::BeginScene(m_Camera);

		Inno::Renderer::Submit(m_TriangleShader, m_TriangleVA);

		Inno::Renderer::EndScene();
	}

	virtual void OnGuiRender() override
	{

	}

	virtual void OnEvent(Inno::Event& event) override
	{

	}

private:
	std::shared_ptr<Inno::Shader> m_TriangleShader;
	std::shared_ptr<Inno::VertexArray> m_TriangleVA;

	Inno::Camera m_Camera;
};

class App : public Inno::Application
{
public:
	App()
	{
		Inno::Renderer::Command::SetAPI(Inno::RendererAPI::API::OpenGL);
		PushLayer(new ExampleLayer());
	}

	~App() {}
};

/**
 * @brief This is used for the transfering the app instance into the entry point.
 */
Inno::Application* Inno::CreateApplication()
{
	return new App();
}
