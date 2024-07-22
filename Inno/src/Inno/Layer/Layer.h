#pragma once

#include "Inno/Event/Event.h"

namespace Inno
{
    class Layer
    {
    public:

        Layer(const std::string& name = "Layer")
            : m_Name(name) {}
        virtual ~Layer() = default;

        /**
         * @brief Called when the layer is attached.
         */
        virtual void OnAttach() {}

        /**
         * @brief Called when the layer is detached.
         */
        virtual void OnDetach() {}

        /**
         * @brief Called every frame to update the layer.
         */
        virtual void OnUpdate() {}

        /**
         * @brief Called to handle the GUI events of this layer.
         */
        virtual void OnGuiRender() {}

        /**
         * @brief Called when an event occurs.
         * @param event The event that occurred.
         */
        virtual void OnEvent(Event& event) {}

        /**
         * @brief Returns the name of the layer.
         * @returns The name of the layer.
         */
        const std::string& GetName() const { return m_Name; }

        /**
         * @brief Conversion operator to convert the layer to its name.
         * @returns The name of the layer.
         */
        operator std::string() const
        {
            return GetName();
        }

    protected:
        /**
         * @brief The name of the layer.
         */
        std::string m_Name;
    };
}
