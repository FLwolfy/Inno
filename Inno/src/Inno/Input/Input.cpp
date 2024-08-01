#include "pch.h"
#include "Input.h"

#include "Inno/Core/Application.h"

namespace Inno
{
	Input* Input::s_Instance = new Input();

	bool Input::IsKeyPressedImpl(const Keycode keycode)
	{
		InputState state = Application::Get().GetWindow().GetKeyState(static_cast<int32_t>(keycode));
		return state == InputState::Pressed || state == InputState::Repeat;
	}

	bool Input::IsMouseButtonPressedImpl(const Mousecode mousecode)
	{
		InputState state = Application::Get().GetWindow().GetMouseButtonState(static_cast<int32_t>(mousecode));
		return state == InputState::Pressed;
	}

	glm::vec2 Input::GetMousePositionImpl()
	{
		return Application::Get().GetWindow().GetCursorPosPosition();
	}

	float Input::GetMouseXImpl()
	{
		return GetMousePositionImpl().x;
	}

	float Input::GetMouseYImpl()
	{
		return GetMousePositionImpl().y;
	}
}
