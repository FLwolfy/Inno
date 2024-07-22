#include "pch.h"
#include "Application.h"

#include "Inno/Core/Core.h"
#include "Inno/Core/Log.h"
#include "Inno/Core/Timestep.h"
#include "Inno/Input/Input.h"

#include "Inno/Render/Renderer.h"

// Temporary
#include <GLFW/glfw3.h>

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
		Renderer::Command::Init();
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

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.IsHandled)
			{
				break;
			}

			(*it)->OnEvent(event);
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

			for (Layer* layer : m_LayerStack)
			{
				layer->OnGuiRender();
			}

			m_ImGuiLayer->End();

			// Main Window Application Loop
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_IsRunning = false;
		return true;
	}
}
