#pragma once

#include "Inno/Core/Window.h"

namespace Inno
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	/*
	Defined in client
	*/ 
	Application* CreateApplication();
}


