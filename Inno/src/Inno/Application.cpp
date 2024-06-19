#include "pch.h"
#include "Application.h"

#include "Inno/Log.h"
#include "Inno/Events/ApplicationEvent.h"	

namespace Inno
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		INNO_LOGTRACE(e);

		while (true);
	}
}
