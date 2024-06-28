#pragma once

#include "Inno/Input/Keycode.h"
#include "Inno/Input/Mousecode.h"


namespace Inno
{
	class Input
	{
	public:
		static bool IsKeyPressed(const Keycode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(const Mousecode mousecode) { return s_Instance->IsMouseButtonPressed(mousecode); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
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

