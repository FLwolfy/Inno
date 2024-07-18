#include <Inno.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

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

		Inno::Ref<Inno::VertexBuffer> triangleVB = Inno::VertexBuffer::Create(vertices, sizeof(vertices));

		Inno::ShaderDataType t = Inno::ShaderDataType::Float;
		triangleVB->SetLayout({
			{ Inno::ShaderDataType::Float3, "a_Position" },
			{ Inno::ShaderDataType::Float4, "a_Color"}
		});

		uint32_t indices[3] = { 0, 1, 2 };
		Inno::Ref<Inno::IndexBuffer> triangleIB = Inno::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_TriangleVA->AddVertexBuffer(triangleVB);
		m_TriangleVA->SetIndexBuffer(triangleIB);

		std::string shaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_CameraVP;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_CameraVP * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string shaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec3 v_Position;
			in vec4 v_Color;

			uniform float u_ColorHue;

			void main()
			{
				o_Color = vec4(u_ColorHue * v_Color.r, u_ColorHue * v_Color.g, u_ColorHue * v_Color.b, v_Color.a);
			}
		)";

		m_TriangleShader = Inno::Shader::Create("Triangle Shader", shaderVertexSrc, shaderFragmentSrc);
	}

	virtual void OnUpdate() override
	{
		// Test Delta Time
		// INNO_LOGTRACE(Inno::Timestep::GetDeltaTimeSeconds());
		INNO_LOGTRACE(m_TriangleColorHue);

		// Test Render
		Inno::Renderer::Command::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Inno::Renderer::Command::Clear();

		m_Camera.SetPosition({ 0.25f, 0.0f, 0.0f });
		m_Camera.SetRotation({ 0.0f, 0.0f, 180.0f });

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		m_TriangleShader->SetUniformFloat("u_ColorHue", m_TriangleColorHue);

		Inno::Renderer::BeginScene(m_Camera);

		for (int x = 0; x < 10; x++)
		{
			glm::vec3 position = glm::vec3(x * 0.11f, 0.0f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
			Inno::Renderer::Submit(m_TriangleShader, m_TriangleVA, transform);
		}

		Inno::Renderer::EndScene();
	}

	virtual void OnGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::SliderFloat("Triangle Hue", &m_TriangleColorHue, 0.0f, 1.0f, "Hue: %.1f");

		ImGui::End();
	}

	virtual void OnEvent(Inno::Event& event) override
	{

	}

private:
	Inno::Camera m_Camera;

	Inno::Ref<Inno::Shader> m_TriangleShader;
	Inno::Ref<Inno::VertexArray> m_TriangleVA;
	float m_TriangleColorHue = 1.0f;
};

class App : public Inno::Application
{
public:
	virtual void InitSettings() override
	{
		Inno::Window::Command::SetAPI(Inno::Window::API::OpenGL);
		Inno::Renderer::Command::SetAPI(Inno::RendererAPI::API::OpenGL);
	}

	virtual void Start() override
	{
		PushLayer(new ExampleLayer());
	}
};

/**
 * @brief This is used for the transfering the app instance into the entry point.
 */
Inno::Application* Inno::CreateApplication()
{
	return new App();
}
