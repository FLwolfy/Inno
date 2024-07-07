#pragma once

#include "Inno/Input/Keycode.h"
#include "Inno/Input/Mousecode.h"


namespace Inno
{
    /**
     * @brief Static class for handling input queries.
     */
    class Input
    {
    public:
        /**
         * @brief Checks if a key is currently pressed.
         * @param keycode The keycode of the key to check.
         * @return True if the key is pressed, false otherwise.
         */
        static bool IsKeyPressed(const Keycode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

        /**
         * @brief Checks if a mouse button is currently pressed.
         * @param mousecode The mousecode of the button to check.
         * @return True if the mouse button is pressed, false otherwise.
         */
        static bool IsMouseButtonPressed(const Mousecode mousecode) { return s_Instance->IsMouseButtonPressedImpl(mousecode); }

        /**
         * @brief Retrieves the current mouse position.
         * @return A pair containing the x and y coordinates of the mouse position.
         */
        static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

        /**
         * @brief Retrieves the current x-coordinate of the mouse position.
         * @return The x-coordinate of the mouse position.
         */
        static float GetMouseX() { return s_Instance->GetMouseXImpl(); }

        /**
         * @brief Retrieves the current y-coordinate of the mouse position.
         * @return The y-coordinate of the mouse position.
         */
        static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	private:
		static Input* s_Instance;

	private:
		bool IsKeyPressedImpl(const Keycode keycode);
		bool IsMouseButtonPressedImpl(const Mousecode mousecode);
		std::pair<float, float> GetMousePositionImpl();
		float GetMouseXImpl();
		float GetMouseYImpl();
	};
}

