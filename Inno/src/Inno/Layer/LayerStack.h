#pragma once

#include <pch.h> // Assuming pch.h is a precompiled header file

#include "Inno/Layer/Layer.h"

namespace Inno
{
    /**
     * @brief Class representing a stack of layers.
     */
    class LayerStack
    {
    public:
        /**
         * @brief Default constructor for LayerStack.
         */
        LayerStack() = default;

        /**
         * @brief Destructor for LayerStack.
         */
        ~LayerStack();

        /**
         * @brief Pushes a layer onto the stack.
         * @param layer Pointer to the layer to be pushed.
         */
        void PushLayer(Layer* layer);

        /**
         * @brief Pushes an overlay onto the stack.
         * @param overlay Pointer to the overlay to be pushed.
         */
        void PushOverlay(Layer* overlay);

        /**
         * @brief Pops a layer from the stack.
         * @param layer Pointer to the layer to be popped.
         */
        void PopLayer(Layer* layer);

        /**
         * @brief Pops an overlay from the stack.
         * @param overlay Pointer to the overlay to be popped.
         */
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
        std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
        std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
        std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
        std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
        std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerSplitIndex = 0;
    };
}
