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

		// Vertex Array Create
		m_VA = Inno::VertexArray::Create();

		// Frame Buffer Create
		Inno::FrameBufferProperties FBprop;
		FBprop.AttachmentProps = { Inno::FrameBufferAttachmentFormat::RGBA8, Inno::FrameBufferAttachmentFormat::RED_INTEGER, Inno::FrameBufferAttachmentFormat::Depth };
		FBprop.Width = 1280;
		FBprop.Height = 720;
		m_FB = Inno::FrameBuffer::Create(FBprop);
	}

	virtual void OnAttach() override
	{
		// Camera Initialization
		m_Camera.SetPosition({ 0.25f, 0.0f, 0.0f });
		m_Camera.SetRotation({ 0.0f, 0.0f, 0.0f });

		// Vertex Array Initialization
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
		// Resize
		if (Inno::FrameBufferProperties prop = m_FB->GetProperties(); m_ViewportPanelSize.x > 0.0f && m_ViewportPanelSize.y > 0.0f && (prop.Width != m_ViewportPanelSize.x || prop.Height != m_ViewportPanelSize.y))
		{
			m_FB->Resize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);
			m_Camera.Resize(m_ViewportPanelSize.x, m_ViewportPanelSize.y);
		}

		// Render
		Inno::Application::Get().SetImGuiBlock(!m_ViewportFocus);
		if (m_ViewportFocus)
		{
			m_Camera.OnUpdate();
		}

		m_FB->Bind();
		m_Texture->BindSlot(0); // Temporary

		Inno::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Inno::RendererCommand::Clear();

		Inno::Ref<Inno::Shader> shader = Inno::Renderer::GetShaderLibrary().Get("texture");
		shader->SetUniformFloat("u_Visibility", m_Visibility);

		Inno::Renderer::BeginScene(m_Camera);
		Inno::Renderer::Submit(shader, m_VA, glm::translate(glm::mat4(1.0f), glm::vec3(0.11f, 0.0f, 0.0f)));
		Inno::Renderer::EndScene();

		m_FB->Unbind();
	}

	virtual void OnGuiRender() override
	{
		// Settings
		ImGui::Begin("Settings");
		ImGui::SliderFloat("Visibility", &m_Visibility, 0.0f, 1.0f, "%.1f");
		ImGui::End();

		// Viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		m_ViewportPanelSize = { viewportSize.x , viewportSize.y };
		m_ViewportFocus = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();

		ImGui::Image(reinterpret_cast<void*>(static_cast<uintptr_t>(m_FB->GetAttachmentRendererID())), ImVec2{ m_ViewportPanelSize.x, m_ViewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();
	}

	virtual void OnEvent(Inno::Event& event) override
	{
		m_Camera.OnEvent(event);
	}

private:
	Inno::Camera m_Camera;

	Inno::Ref<Inno::FrameBuffer> m_FB;
	Inno::Ref<Inno::VertexArray> m_VA;
	Inno::Ref<Inno::Texture> m_Texture;

	float m_Visibility = 1.0f;
	bool m_ViewportFocus = false;
	glm::vec2 m_ViewportPanelSize = { 0,0 };
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
