#include "pch.h"
#include "Application.h"

#include "Inno/Core/Core.h"
#include "Inno/Core/Log.h"
#include "Inno/Core/Timestep.h"
#include "Inno/Input/Input.h"

#include "Inno/Render/Renderer.h"

// Temporary
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Inno
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		/* Singleton Application */
		INNO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
	}

	void Application::Init()
	{
		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_FUNC(Application::OnEvent, this));
		m_ImGuiLayer = ImGuiLayer::Create();
		Renderer::Init();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& event)
	{
		event.Dispatch<WindowCloseEvent>(BIND_FUNC(Application::OnWindowClose, this));

		// DEBUG: LOG EVENT DETAILS
		// INNO_CORE_LOGTRACE(event);

		for (auto layer = m_LayerStack.rbegin(); layer != m_LayerStack.rend(); ++layer)
		{
			if (event.IsHandled)
			{
				break;
			}

			(*layer)->OnEvent(event);
		}
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			// Time Step
			float time = m_Window->GetWindowTime();
			Timestep::m_Time = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Layer Updating
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			// Gui Rendering
			m_ImGuiLayer->Begin();
			HandleDockspaceGui();
			m_ImGuiLayer->End();

			// Main Window Application Loop
			m_Window->OnUpdate();
		}
	}

	void Application::HandleDockspaceGui()
	{
		// DEBUG: Set this to false to disable dockspace
		static bool dockspace_enable = true;
		if (dockspace_enable)
		{
			static bool dockspace_open = true;
			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}
			else
			{
				dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
			// and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspace_open, window_flags);
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// Submit the DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					// Here to add selections on the top left corner.
					if (ImGui::MenuItem("Exit")) m_IsRunning = false;
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			// Handle Layers Gui Render
			for (Layer* layer : m_LayerStack)
			{
				layer->OnGuiRender();
			}

			ImGui::End();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_IsRunning = false;
		return true;
	}
}
