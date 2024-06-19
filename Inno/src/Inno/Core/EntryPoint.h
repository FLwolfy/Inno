#pragma once

#ifdef INNO_PLATFORM_WINDOWS

extern Inno::Application* Inno::CreateApplication();

int main(int argc, char** argv)
{
	// Temporary
	Inno::Log::Init();
	INNO_LOGINFO("Welcome to Inno Engine!");

	auto app = Inno::CreateApplication();
	app->Run();
	delete app;
}

#endif

