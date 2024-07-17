#include "pch.h"
#include "Input.h"

#include "Inno/Core/Application.h"
#include "GLFW/glfw3.h"

namespace Inno
{
	Input* Input::s_Instance = new Input();

	bool Input::IsKeyPressedImpl(const Keycode keycode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowHandle());
		int state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressedImpl(const Mousecode mousecode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowHandle());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(mousecode));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePositionImpl()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowHandle());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float Input::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
