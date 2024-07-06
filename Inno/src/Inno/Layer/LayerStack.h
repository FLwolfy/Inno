#pragma once

#include <pch.h>

#include "Inno/Layer/Layer.h"

namespace Inno
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

        /// <summary>
        /// Pushes a layer onto the stack.
        /// </summary>
        /// <param name="layer">: Pointer to the layer to be pushed.</param>
        void PushLayer(Layer* layer);

        /// <summary>
        /// Pushes an overlay onto the stack.
        /// </summary>
        /// <param name="overlay">: Pointer to the overlay to be pushed.</param>
        void PushOverlay(Layer* overlay);

        /// <summary>
        /// Pops a layer from the stack.
        /// </summary>
        /// <param name="layer">: Pointer to the layer to be popped.</param>
        void PopLayer(Layer* layer);

        /// <summary>
        /// Pops an overlay from the stack.
        /// </summary>
        /// <param name="overlay">: Pointer to the overlay to be popped.</param>
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

