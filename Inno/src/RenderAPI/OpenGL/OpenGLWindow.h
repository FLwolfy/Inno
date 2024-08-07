#pragma once

#include "Inno/Core/Window.h"

namespace Inno
{
	class OpenGLWindow : public Window
	{
    public:
        OpenGLWindow(const WindowProperties& properties = WindowProperties());
        ~OpenGLWindow();

        /**
         * @brief Updates the OpenGL window.
         */
        virtual void OnUpdate() override;
        /**
         * @brief Sets whether vertical sync (VSync) is enabled.
         * @param enabled True to enable VSync, false otherwise.
         */
        virtual void SetVSync(bool enabled) override;
        /**
         * @brief Checks if VSync is currently enabled.
         * @return True if VSync is enabled, false otherwise.
         */
        virtual bool IsVSync() const override;
        /**
         * @brief Gets the current frame time of this window render.
         */
        virtual float GetWindowTime() const override;

        /**
         * @brief Retrieves the current state of the specified key.
         * @param key The key to check.
         * @return The current state of the key.
         */
        virtual InputState GetKeyState(int key) const override;
        /**
         * @brief Retrieves the current state of the specified mousebutton.
         * @param button The mouse button to check.
         * @return The current state of the mouse button.
         */
        virtual InputState GetMouseButtonState(int button) const override;
        /**
         * @brief Retrieves the current position of the cursors.
         */
        virtual glm::vec2 GetCursorPosPosition() const override;

    private:
        static unsigned int s_GLFWWindowCount;
	};
}

