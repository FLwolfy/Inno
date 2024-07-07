#pragma once

#include "Inno/Layer/Layer.h"
#include "Inno/Event/ApplicationEvent.h"
#include "Inno/Event/MouseEvent.h"
#include "Inno/Event/KeyEvent.h"

namespace Inno
{
    /**
     * @brief Layer for ImGui integration.
     */
    class ImGuiLayer : public Layer
    {
    public:
        /**
         * @brief Default constructor.
         */
        ImGuiLayer();
        
        /**
         * @brief Default destructor.
         */
        ~ImGuiLayer() = default;
        
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
         * @brief Begins the ImGui window rendering.
         */
        void Begin();
        
        /**
         * @brief Ends the ImGui window rendering.
         */
        void End();
        
    private:
        float m_Time = 0.0f;
    };
}
