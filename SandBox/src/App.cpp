#include <Inno.h>

class ExampleLayer : public Inno::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	virtual void OnUpdate() override
	{
		INNO_LOGINFO("ExampleLayer Update!");
	}
};

class App : public Inno::Application
{
public:
	App() { PushLayer(new ExampleLayer()); }

	~App() {}
};

/*
This is used for the transfering the app instance into the entry point.
*/
Inno::Application* Inno::CreateApplication()
{
	return new App();
}