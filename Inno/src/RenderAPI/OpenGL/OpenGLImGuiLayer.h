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
         * @brief Called when an event occurs.
         * @param event The event that occurred.
         */
        virtual void OnEvent(Event& event) override;
        /**
         * @brief Called in between the Begin() and End() for rendering ImGui windows.
         */
        virtual void OnGuiRender() override;

        /**
         * @brief Begins the OpenGL ImGui window rendering.
         */
        virtual void Begin() override;
        /**
         * @brief Ends the OpenGL ImGui window rendering.
         */
        virtual void End() override;

        /**
         * @brief Sets whether the Imgui will handle the events.
         */
        virtual void SetBlockEvent(bool doBlockEvents) override { m_BlockEvents = doBlockEvents; }

    private:
        bool m_BlockEvents = true;
	};
}

