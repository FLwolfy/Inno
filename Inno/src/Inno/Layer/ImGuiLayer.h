#pragma once

#include "Inno/Layer/Layer.h"
#include "Inno/Event/ApplicationEvent.h"
#include "Inno/Event/MouseEvent.h"
#include "Inno/Event/KeyEvent.h"

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
        /// Called when the layer is detached from the layer stack.
        /// Cleans up ImGui resources.
        /// </summary>
        virtual void OnDetach() override;

        /// <summary>
        /// Called in between the Begin() and End() for rendering ImGui windows.
        /// </summary>
        virtual void OnGuiRender() override;

        /// <summary>
        /// Begins the Imgui Window Rendering.
        /// </summary>
        void Begin();

        /// <summary>
        /// Ends the Imgui Window Rendering.
        /// </summary>
        void End();

	private:
		float m_Time = 0.0f;
	};
}

