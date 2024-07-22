#pragma once

/**
 * @brief Declares an external function for creating an Application instance.
 * @return Pointer to the newly created Application instance.
 */
extern Inno::Application* Inno::CreateApplication();

int main(int argc, char** argv)
{
	// Temporary
	Inno::Log::Init();
	INNO_LOGINFO("Welcome to Inno Engine!");

	auto app = Inno::CreateApplication();
	app->InitSettings();
	app->Init();
	app->Start();
	app->Run();
	delete app;
}

