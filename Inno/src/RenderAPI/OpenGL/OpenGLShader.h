#pragma once

#include "Inno/Render/Shader.h"

#include <glad/glad.h>

namespace Inno
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        OpenGLShader(const std::string& filepath);
        ~OpenGLShader();

        /**
         * @brief Binds the shader for use in rendering.
         */
        virtual void Bind() const override;
        /**
         * @brief Unbinds the shader. Mostly for debug use.
         */
        virtual void Unbind() const override;

        /**
         * @brief Sets an integer uniform in the OpenGL shader program.
         * @param name The name of the uniform variable.
         * @param value The integer value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformInt(const std::string& name, int value) override;
        /**
         * @brief Sets an array of integer uniforms in the OpenGL shader program.
         * @param name The name of the uniform array variable.
         * @param values Pointer to the array of integer values.
         * @param count The number of elements in the array.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformIntArray(const std::string& name, int* values, uint32_t count) override;
        /**
         * @brief Sets a float uniform in the OpenGL shader program.
         * @param name The name of the uniform variable.
         * @param value The float value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformFloat(const std::string& name, float value) override;
        /**
         * @brief Sets a 2D float vector uniform in the OpenGL shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::vec2 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformFloat2(const std::string& name, const glm::vec2& value) override;
        /**
         * @brief Sets a 3D float vector uniform in the OpenGL shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::vec3 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) override;
        /**
         * @brief Sets a 4D float vector uniform in the OpenGL shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::vec4 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) override;
        /**
         * @brief Sets a 3x3 float matrix uniform in the OpenGL shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::mat3 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) override;
        /**
         * @brief Sets a 4x4 float matrix uniform in the OpenGL shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::mat4 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override;

    private:
        uint32_t m_RendererID;

    private:
        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> SplitShaders(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);
    };

}
