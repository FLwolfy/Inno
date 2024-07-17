#pragma once

namespace Inno {

    /**
     * @brief Abstract base class representing a graphics context.
     * Provides an interface for initializing and managing the rendering context.
     */
    class GraphicsContext
    {
    public:
        /**
         * @brief Destructor for GraphicsContext.
         */
        virtual ~GraphicsContext() = default;

        /**
         * @brief Initializes the graphics context.
         */
        virtual void Init() = 0;

        /**
         * @brief Swaps the front and back render buffers.
         */
        virtual void SwapBuffers() = 0;
    };

}
