#pragma once

#include "pch.h"
#include "Inno/Events/Event.h"

#include <GLFW/glfw3.h>

namespace Inno
{
	/// <summary>
	/// Structure holding window properties such as title, width, and height.
	/// </summary>
	struct WindowProperties
	{
	public:
		std::string Title;          ///< The title of the window.
		unsigned int Width;         ///< The width of the window.
		unsigned int Height;        ///< The height of the window.

		/// <summary>
		/// Constructs window properties with specified title, width, and height.
		/// </summary>
		/// <param name="title">: The title of the window.</param>
		/// <param name="width">: The width of the window.</param>
		/// <param name="height">: The height of the window.</param>
		WindowProperties(const std::string& title = "Inno Engine",
			unsigned int width = 1600,
			unsigned int height = 900)
			: Title(title), Width(width), Height(height) {}
	};

    /// <summary>
    /// Window class using GLFW for window management.
    /// </summary>
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;   ///< Event callback function type.

        /// <summary>
        /// Constructs a window with the specified properties.
        /// </summary>
        /// <param name="properties">: The properties of the window.</param>
        Window(const WindowProperties& properties);

        /// <summary>
        /// Virtual destructor for the window class.
        /// </summary>
        virtual ~Window();

        /// <summary>
        /// Updates the window.
        /// </summary>
        virtual void OnUpdate();

        /// <summary>
        /// Sets whether vertical sync (VSync) is enabled.
        /// </summary>
        /// <param name="enabled">: True to enable VSync, false otherwise.</param>
        virtual void SetVSync(bool enabled);

        /// <summary>
        /// Checks if VSync is currently enabled.
        /// </summary>
        /// <returns>True if VSync is enabled, false otherwise.</returns>
        virtual bool IsVSync() const;

        /// <summary>
        /// Retrieves the width of the window.
        /// </summary>
        /// <returns>The width of the window.</returns>
        inline unsigned int GetWidth() const { return m_Data.Width; }

        /// <summary>
        /// Retrieves the height of the window.
        /// </summary>
        /// <returns>The height of the window.</returns>
        inline unsigned int GetHeight() const { return m_Data.Height; }

        /// <summary>
        /// Sets the event callback function for handling window events.
        /// </summary>
        /// <param name="callback">: The event callback function.</param>
        inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

        /// <summary>
        /// Creates a new window with the specified properties.
        /// </summary>
        /// <param name="properties">: The properties of the window to be created.</param>
        /// <returns>A pointer to the newly created Window object.</returns>
        static Window* Create(const WindowProperties& properties = WindowProperties());

	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		GLFWwindow* m_Window;
	};
}

