#include "pch.h"
#include "Application.h"

#include "Inno/Core/Log.h"
#include "Inno/Events/ApplicationEvent.h"

namespace Inno
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			m_Window->OnUpdate();
		}
	}
}
