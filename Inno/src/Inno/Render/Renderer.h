#pragma once

namespace Inno
{
    /* Enum representing different rendering APIs supported. */
    enum class RendererAPI
    {
        None = 0,   ///< No rendering API
        OpenGL = 1  ///< OpenGL rendering API
    };

    /* Renderer class responsible for managing the current rendering API.*/
    class Renderer
    {
    public:
        /**
         * @brief Retrieves the current rendering API in use.
         *
         * @returns The current rendering API.
         */
        inline static RendererAPI GetAPI() { return s_RendererAPI; }

    private:
        static RendererAPI s_RendererAPI; ///< Currently active rendering API
    };

}
