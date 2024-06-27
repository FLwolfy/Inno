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

        /// <summary>
        /// Returns the singleton instance of the application.
        /// </summary>
        /// <returns>Reference to the singleton Application instance.</returns>
        inline static Application& Get() { return *s_Instance; }

        /// <summary>
        /// Returns the window associated with the application.
        /// </summary>
        /// <returns>Reference to the application's window.</returns>
        inline Window& GetWindow() { return *m_Window; }

        /// <summary>
        /// Pushes a layer onto the application's layer stack.
        /// </summary>
        /// <param name="layer">: Pointer to the layer to be pushed.</param>
        void PushLayer(Layer* layer);

        /// <summary>
        /// Pushes an overlay onto the application's layer stack.
        /// </summary>
        /// <param name="layer">: Pointer to the layer to be pushed.</param>
        void PushOverlay(Layer* layer);

        /// <summary>
        /// Handles an event by dispatching it to the relevant layers.
        /// </summary>
        /// <param name="event">: Reference to the event to be handled.</param>
        void OnEvent(Event& event);

        /// <summary>
        /// Starts the main application loop.
        /// </summary>
        void Run();

	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& event);
	};

    /// <summary>
    /// Defined in client.
    /// Creates and returns a new application instance.
    /// </summary>
    /// <returns>Pointer to the newly created Application instance.</returns>
    Application* CreateApplication();
}


