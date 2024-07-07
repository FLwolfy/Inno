#pragma once

#include "pch.h"
#include "Inno/Event/Event.h"
#include "Inno/Render/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Inno
{
    /**
     * @brief Structure holding window properties such as title, width, and height.
     */
    struct WindowProperties
    {
    public:
        std::string Title;          ///< The title of the window.
        unsigned int Width;         ///< The width of the window.
        unsigned int Height;        ///< The height of the window.

    public:
        /**
         * @brief Constructs window properties with specified title, width, and height.
         * @param title The title of the window.
         * @param width The width of the window.
         * @param height The height of the window.
         */
        WindowProperties(const std::string& title = "Inno Engine",
                         unsigned int width = 1600,
                         unsigned int height = 900)
            : Title(title), Width(width), Height(height) {}
    };

    /**
     * @brief Window class using GLFW for window management.
     */
    class Window
    {
        using EventCallbackFn = std::function<void(Event&)>;   ///< Event callback function type.

        /**
         * @brief Internal data structure for storing window-specific data.
         */
        struct WindowData
        {
            std::string Title;          ///< The title of the window.
            unsigned int Width, Height;  ///< The width and height of the window.
            bool VSync;                  ///< Flag indicating whether VSync is enabled.
            EventCallbackFn EventCallback;  ///< Callback function for handling events.
        };

    public:
        /**
         * @brief Constructs a window with the specified properties.
         * @param properties The properties of the window.
         */
        Window(const WindowProperties& properties);

        /**
         * @brief Virtual destructor for the window class.
         */
        ~Window();

        /**
         * @brief Creates a new window with the specified properties.
         * @param properties The properties of the window to be created.
         * @return A pointer to the newly created Window object.
         */
        static Window* Create(const WindowProperties& properties = WindowProperties());

        /**
         * @brief Updates the window.
         */
        void OnUpdate();

        /**
         * @brief Sets whether vertical sync (VSync) is enabled.
         * @param enabled True to enable VSync, false otherwise.
         */
        void SetVSync(bool enabled);

        /**
         * @brief Checks if VSync is currently enabled.
         * @return True if VSync is enabled, false otherwise.
         */
        bool IsVSync() const;

        /**
         * @brief Retrieves the width of the window.
         * @return The width of the window.
         */
        inline unsigned int GetWidth() const { return m_Data.Width; }

        /**
         * @brief Retrieves the height of the window.
         * @return The height of the window.
         */
        inline unsigned int GetHeight() const { return m_Data.Height; }

        /**
         * @brief Gets the native GLFW window instance of the current window.
         * @return The native GLFW window instance.
         */
        inline GLFWwindow* GetNativeWindow() const { return m_Window; }

        /**
         * @brief Sets the event callback function for handling window events.
         * @param callback The event callback function.
         */
        inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

    private:
        WindowData m_Data;       ///< Window data structure.
        GLFWwindow* m_Window;    ///< GLFW window handle.
        GraphicsContext* m_Context;  ///< Graphics context for the window.
    };
}
