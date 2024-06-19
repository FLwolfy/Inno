#pragma once

#include "Core.h"

namespace Inno
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	/*
	Defined in client
	*/ 
	Application* CreateApplication();
}


