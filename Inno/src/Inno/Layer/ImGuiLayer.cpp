#include "pch.h"
#include "ImGuiLayer.h"

#include "Inno/Core/Window.h"

#include "RenderAPI/OpenGL/OpenGLImGuiLayer.h"

namespace Inno
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {}


	ImGuiLayer* ImGuiLayer::Create()
	{
		switch (Window::Command::GetAPI())
		{
			case Window::API::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "Window::API::None current not supported!");
				return nullptr;
			}
			case Window::API::OpenGL:
			{
				return new OpenGLImGuiLayer();
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
			}
		}
	}
}
