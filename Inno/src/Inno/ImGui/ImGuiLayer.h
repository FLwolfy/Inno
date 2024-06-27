#pragma once

#include "Inno/Core/Layer.h"
#include "Inno/Events/ApplicationEvent.h"
#include "Inno/Events/MouseEvent.h"
#include "Inno/Events/KeyEvent.h"

namespace Inno
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

        /// <summary>
        /// Called when the layer is attached to the application.
        /// Initializes ImGui and sets up ImGui specific settings.
        /// </summary>
        virtual void OnAttach() override;

        /// <summary>
        /// Called when the layer is detached from the application.
        /// Cleans up ImGui resources.
        /// </summary>
        virtual void OnDetach() override;

        /// <summary>
        /// Called once per frame to update ImGui, typically called before rendering.
        /// </summary>
        virtual void OnUpdate() override;

        /// <summary>
        /// Handles ImGui events, such as mouse clicks and keyboard input.
        /// </summary>
        /// <param name="event">The event to handle.</param>
        virtual void OnEvent(Event& event) override;

	private:
		float m_Time = 0.0f;

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
	};
}

