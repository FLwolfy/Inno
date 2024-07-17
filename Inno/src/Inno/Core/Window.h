#pragma once

#include "Inno/Event/Event.h"
#include "Inno/Render/GraphicsContext.h"

namespace Inno
{
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;   /// Event callback function type.

        /**
         * @brief Enumeration of supported Window APIs.
         */
        enum class API
        {
            None = 0,   /// No specific rendering API selected.
            OpenGL      /// OpenGL rendering API.
        };

        class Command
        {
        public:
            /**
             * @brief Retrieves the current Window API.
             */
            static inline API GetAPI() { return s_WindowAPI; }
            /**
             * @brief Sets the current Window API.
             */
            static inline void SetAPI(API api) { s_WindowAPI = api; }
        };

        /**
         * @brief Internal structure for storing window properties.
         */
        struct WindowProperties
        {
        public:
            std::string Title;          /// The title of the window.
            unsigned int Width;         /// The width of the window.
            unsigned int Height;        /// The height of the window.

        public:
            WindowProperties(const std::string& title = "Inno Engine",
                unsigned int width = 1600,
                unsigned int height = 900)
                : Title(title), Width(width), Height(height) {}
        };

        /**
         * @brief Internal structure for storing window-specific data.
         */
        struct WindowData
        {
        public:
            std::string Title;                /// The title of the window.
            unsigned int Width, Height;       /// The width and height of the window.
            bool VSync;                       /// Flag indicating whether VSync is enabled.
            EventCallbackFn EventCallback;    /// Callback function for handling events.
        };

    public:
        Window(const WindowProperties& properties);

        /**
         * @brief Updates the window.
         */
        virtual void OnUpdate() = 0;
        /**
         * @brief Sets whether vertical sync (VSync) is enabled.
         * @param enabled True to enable VSync, false otherwise.
         */
        virtual void SetVSync(bool enabled) = 0;
        /**
         * @brief Checks if VSync is currently enabled.
         * @return True if VSync is enabled, false otherwise.
         */
        virtual bool IsVSync() const = 0;

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
        inline void* GetWindowHandle() const { return m_WindowHandle; }

        /**
         * @brief Sets the event callback function for handling window events.
         * @param callback The event callback function.
         */
        inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

        /**
         * @brief Creates a new window with the specified properties according to the Window Render API.
         * @return A pointer to the newly created Window object.
         */
        static std::unique_ptr<Window> Create(const WindowProperties& properties = WindowProperties());

    protected:
        WindowData m_Data;           /// Window data structure.
        GraphicsContext* m_Context;  /// Graphics context for the window.
        void* m_WindowHandle;        /// Window handle.

    private:
        static API s_WindowAPI;
    };
}
