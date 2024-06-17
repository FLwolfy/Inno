#include <Inno.h>

class App : public Inno::Application
{
public:
	App()
	{

	}

	~App()
	{

	}
};

/*
This is used for the transfering the app instance into the entry point.
*/
Inno::Application* Inno::CreateApplication()
{
	return new App();
}