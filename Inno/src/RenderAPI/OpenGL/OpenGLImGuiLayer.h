#pragma once

#include "Inno/Layer/ImGuiLayer.h"

namespace Inno
{
	class OpenGLImGuiLayer : public ImGuiLayer
	{
	public:
        /**
         * @brief Called when the layer is attached to the application.
         * Initializes ImGui and sets up ImGui specific settings.
         */
        virtual void OnAttach() override;

        /**
         * @brief Called when the layer is detached from the layer stack.
         * Cleans up ImGui resources.
         */
        virtual void OnDetach() override;

        /**
         * @brief Called in between the Begin() and End() for rendering ImGui windows.
         */
        virtual void OnGuiRender() override;

        /**
         * @brief Begins the OpenGL ImGui window rendering.
         */
        void Begin();

        /**
         * @brief Ends the OpenGL ImGui window rendering.
         */
        void End();
	};
}

