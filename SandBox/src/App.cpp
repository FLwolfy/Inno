#include <Inno.h>
#include <Inno/Core/Log.h>

class App : public Inno::Application
{
public:
	App()
	{
	}

	~App() {}
};

/**
 * @brief This is used for the transfering the app instance into the entry point.
 */
std::shared_ptr<Inno::Application> Inno::CreateApplication()
{
	return std::make_shared<App>();
}
