#include <Inno.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

class ExampleLayer : public Inno::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		// Camera Create
		m_Camera = Inno::OrthographicCamera(1280.0f / 720.0f);
		m_Camera.SetPosition({ 0.25f, 0.0f, 0.0f });
		m_Camera.SetRotation({ 30.0f, 45.0f, 180.0f });

		// Vertex Array Create
		m_VA = Inno::VertexArray::Create();

		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Inno::Ref<Inno::VertexBuffer> VB = Inno::VertexBuffer::Create(vertices, sizeof(vertices));

		VB->SetLayout({
			{ Inno::ShaderDataType::Float3, "a_Position" },
			{ Inno::ShaderDataType::Float2, "a_TexCoord" }
		});

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		Inno::Ref<Inno::IndexBuffer> IB = Inno::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_VA->AddVertexBuffer(VB);
		m_VA->SetIndexBuffer(IB);

		// Shader Load
		Inno::Renderer::GetShaderLibrary().Load("assets/shaders/Texture.glsl", "texture");

		// Texture Create
		m_Texture = Inno::Texture2D::Create("assets/textures/coin.png");
		m_Texture->BindSlot(0);
		Inno::Renderer::GetShaderLibrary().Get("texture")->SetUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate() override
	{
		// DEBUG: Test Delta Time
		// INNO_LOGTRACE(Inno::Timestep::GetDeltaTimeSeconds());

		// DEBUG: Test Render
		m_Camera.OnUpdate();

		Inno::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Inno::RendererCommand::Clear();

		Inno::Ref<Inno::Shader> shader = Inno::Renderer::GetShaderLibrary().Get("texture");
		shader->SetUniformFloat("u_Visibility", m_Visibility);

		Inno::Renderer::BeginScene(m_Camera);

		Inno::Renderer::Submit(shader, m_VA, glm::translate(glm::mat4(1.0f), glm::vec3(0.11f, 0.0f, 0.0f)));

		Inno::Renderer::EndScene();
	}

	virtual void OnGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::SliderFloat("Visibility", &m_Visibility, 0.0f, 1.0f, "Hue: %.1f");

		ImGui::End();
	}

	virtual void OnEvent(Inno::Event& event) override
	{
		m_Camera.OnEvent(event);
	}

private:
	Inno::Camera m_Camera;

	Inno::Ref<Inno::VertexArray> m_VA;
	Inno::Ref<Inno::Texture> m_Texture;

	float m_Visibility = 1.0f;
};

class App : public Inno::Application
{
public:
	virtual void InitSettings() override
	{
		Inno::Window::SetAPI(Inno::Window::API::OpenGL);
		Inno::Renderer::SetAPI(Inno::RendererAPI::API::OpenGL);
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
