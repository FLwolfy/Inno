#pragma once

#include "Core.h"

namespace Inno
{
	class INNO_API Application
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


