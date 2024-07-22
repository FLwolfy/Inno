#pragma once

#include "Inno/Core/Window.h"
#include "Inno/Layer/Layer.h"
#include "Inno/Layer/LayerStack.h"
#include "Inno/Layer/ImGuiLayer.h"
#include "Inno/Event/ApplicationEvent.h"

namespace Inno
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        /**
         * @brief Returns the singleton instance of the application.
         * @return Reference to the singleton Application instance.
         */
        inline static Application& Get() { return *s_Instance; }

        /**
         * @brief Returns the window associated with the application.
         * @return Reference to the application's window.
         */
        inline Window& GetWindow() { return *m_Window; }

        /**
         * @brief Pushes a layer onto the application's layer stack.
         * @param layer Pointer to the layer to be pushed.
         */
        void PushLayer(Layer* layer);

        /**
         * @brief Pushes an overlay onto the application's layer stack.
         * @param layer Pointer to the layer to be pushed.
         */
        void PushOverlay(Layer* layer);

        /**
         * @brief Handles an event by dispatching it to the relevant layers.
         * @param event Reference to the event to be handled.
         */
        void OnEvent(Event& event);

        /**
         * @brief Runs the main application loop.
         */
        void Run();

        /**
         * @brief Initializes the application window.
         */
        void InitWindow();

        /**
         * @brief Initiates the application settings at the very beginning right after the construtor.
         */
        virtual void InitSettings() = 0;

        /**
         * @brief Starts the application after the Initialization.
         */
        virtual void Start() = 0;

    private:
        static Application* s_Instance;

        Window* m_Window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_LayerStack;
        bool m_IsRunning = true;
        float m_LastFrameTime = 0.0f;

    private:
        bool OnWindowClose(WindowCloseEvent& event);
    };

    /**
     * @brief Defined in client.
     * Creates and returns a new application instance.
     * @return Pointer to the newly created Application instance.
     */
    Application* CreateApplication();
}
