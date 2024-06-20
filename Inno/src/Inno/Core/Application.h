#pragma once

#include "Inno/Core/Window.h"
#include "Inno/Core/Layer.h"
#include "Inno/Core/LayerStack.h"
#include "Inno/Events/ApplicationEvent.h"

namespace Inno
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void OnEvent(Event& event);
		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& event);
	};

	/*
	Defined in client
	*/ 
	Application* CreateApplication();
}


