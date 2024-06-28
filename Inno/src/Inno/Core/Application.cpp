#include "pch.h"
#include "Application.h"

#include "Inno/Core/Core.h"
#include "Inno/Core/Log.h"
#include "Inno/Input/Input.h"

namespace Inno
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		INNO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_FUNC(Application::OnEvent, this));
	}

	Application::~Application() {}

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
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_IsRunning = false;
		return true;
	}
}
