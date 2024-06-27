#include "pch.h"
#include "ImGuiLayer.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Inno/Core/Core.h"
#include "Inno/Core/Application.h"

// Temporary
#include <glad/glad.h>

namespace Inno
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		ImGui::CreateContext();

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Setup Platform/Renderer bindings
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		event.Dispatch<MouseButtonPressedEvent>(BIND_FUNC(ImGuiLayer::OnMouseButtonPressedEvent, this));
		event.Dispatch<MouseButtonReleasedEvent>(BIND_FUNC(ImGuiLayer::OnMouseButtonReleasedEvent, this));
		event.Dispatch<MouseMovedEvent>	(BIND_FUNC(ImGuiLayer::OnMouseMovedEvent, this));
		event.Dispatch<MouseScrolledEvent>(BIND_FUNC(ImGuiLayer::OnMouseScrolledEvent, this));
		event.Dispatch<KeyPressedEvent>	(BIND_FUNC(ImGuiLayer::OnKeyPressedEvent, this));
		event.Dispatch<KeyReleasedEvent>(BIND_FUNC(ImGuiLayer::OnKeyReleasedEvent, this));
		event.Dispatch<KeyTypedEvent>(BIND_FUNC(ImGuiLayer::OnKeyTypedEvent, this));
		event.Dispatch<WindowResizeEvent>(BIND_FUNC(ImGuiLayer::OnWindowResizeEvent, this));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += event.GetXOffset();
		io.MouseWheel += event.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();;
		int keycode = event.GetKeyCode();
		io.AddInputCharacter(keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());

		return false;
	}

	
}
