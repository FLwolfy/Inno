#pragma once

#include "Inno/Layer/Layer.h"

namespace Inno
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        
        /**
         * @brief Called when the layer is attached to the application.
         * Initializes ImGui and sets up ImGui specific settings.
         */
        virtual void OnAttach() = 0;  
        /**
         * @brief Called when the layer is detached from the layer stack.
         * Cleans up ImGui resources.
         */
        virtual void OnDetach() = 0;   
        /**
         * @brief Called in between the Begin() and End() for rendering ImGui windows.
         */
        virtual void OnGuiRender() = 0;
        /**
         * @brief Begins the ImGui window rendering.
         */
        virtual void Begin() = 0;       
        /**
         * @brief Ends the ImGui window rendering.
         */
        virtual void End() = 0;

        /**
         * @brief Creates a ImGuiLayer with the specified properties according to the Window Render API.
         * @return A pointer to the newly created ImGuiLayer instance.
         */
        static ImGuiLayer* Create();
    };
}
