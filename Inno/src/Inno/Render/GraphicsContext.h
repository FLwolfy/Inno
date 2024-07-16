#pragma once

#include "Inno/Render/RendererAPI.h"

namespace Inno {

    /**
     * @brief Abstract base class representing a graphics context.
     * Provides an interface for initializing and managing the rendering context.
     */
    class GraphicsContext
    {
    public:
        class Command
        {
        public:
            /**
             * @brief Retrieves the current GraphicsContext API.
             */
            static inline RendererAPI::API GetAPI() { return s_ContextAPI; }
            /**
             * @brief Sets the current GraphicContext API.
             */
            static inline void SetAPI(RendererAPI::API api) { s_ContextAPI = api; }
        };

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

        /**
         * @brief Creates the GraphicsContext instance according to the current Window API.
         */
        static GraphicsContext* Create(void* windowHandle);

    private:
        static RendererAPI::API s_ContextAPI;
    };

}
