#pragma once

#include "Inno/Render/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Inno {

    /**
     * @brief OpenGL-specific implementation of the GraphicsContext.
     *        Manages the OpenGL rendering context and buffer swapping.
     */
    class OpenGLContext : public GraphicsContext
    {
    public:
        /**
         * @brief Constructs an OpenGLContext with a specified GLFW window handle.
         * @param windowHandle The handle to the GLFW window.
         */
        OpenGLContext(GLFWwindow* windowHandle);

        /**
         * @brief Initializes the OpenGL context and sets up the necessary OpenGL state and configurations.
         */
        virtual void Init() override;
        /**
         * @brief Swaps the front and back buffers of the OpenGL context. Presents the rendered frame to the screen.
         */
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };

}
