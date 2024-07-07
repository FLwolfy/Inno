#pragma once

#include <string>

#include "Inno/Render/Shader.h"

namespace Inno
{
    class OpenGLShader : public Shader
    {
    public:
        /**
         * @brief Constructs an OpenGLShader with the specified name, vertex source, and fragment source.
         * @param name The name of the shader.
         * @param vertexSrc The vertex shader source code.
         * @param fragmentSrc The fragment shader source code.
         */
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

        ~OpenGLShader();

        /**
         * @brief Binds the shader for use in rendering.
         */
        virtual void Bind() const override;

        /**
         * @brief Unbinds the shader. Mostly for debug use.
         */
        virtual void Unbind() const override;

    private:
        uint32_t m_RendererID;
    };

}
