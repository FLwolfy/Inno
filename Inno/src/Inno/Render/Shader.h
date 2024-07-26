#pragma once

#include "Inno/Core/Core.h"

#include <string>
#include <glm/glm.hpp>

namespace Inno
{
    /**
     * @brief The ShaderDataType used by Inno.
     */
    enum class ShaderDataType
    {
        None = 0,
        Bool,
        Float,
        Float2,
        Float3,
        Float4,
        Int,
        Int2,
        Int3,
        Int4,
        Mat3,
        Mat4
    };

    /**
     * @brief Returns the defined size of the input ShaderDataType.
     * @param type The input ShaderDataType.
     * @return The defined size of the input ShaderDataType.
     */
    static uint32_t GetShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Bool:     return 1;
            case ShaderDataType::Float:    return 4;
            case ShaderDataType::Float2:   return 4 * 2;
            case ShaderDataType::Float3:   return 4 * 3;
            case ShaderDataType::Float4:   return 4 * 4;
            case ShaderDataType::Int:      return 4;
            case ShaderDataType::Int2:     return 4 * 2;
            case ShaderDataType::Int3:     return 4 * 3;
            case ShaderDataType::Int4:     return 4 * 4;
            case ShaderDataType::Mat3:     return 4 * 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4 * 4;

            default:
            {
                INNO_CORE_ASSERT(false, "Unknown ShaderDataType");
                return 0;
            }
        }
    }

    /**
     * @brief Returns the defined component count of the input ShaderDataType.
     * @param type The input ShaderDataType.
     * @return The defined component count of the input ShaderDataType.
     */
    static uint32_t GetShaderDataTypeComponentCount(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Bool:     return 1;
            case ShaderDataType::Float:    return 1;
            case ShaderDataType::Float2:   return 2;
            case ShaderDataType::Float3:   return 3;
            case ShaderDataType::Float4:   return 4;
            case ShaderDataType::Int:      return 1;
            case ShaderDataType::Int2:     return 2;
            case ShaderDataType::Int3:     return 3;
            case ShaderDataType::Int4:     return 4;
            case ShaderDataType::Mat3:     return 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4;
            default:
            {
                INNO_CORE_ASSERT(false, "Unknown ShaderDataType");
                return 0;
            }
        }
    }

    /**
     * @brief Abstract base class for representing a shader in a graphics application.
     */
    class Shader
    {
    public:
        Shader(const std::string& name)
            : m_Name(name) {}
        virtual ~Shader() = default;

        /**
         * @brief Binds the shader for use in rendering.
         */
        virtual void Bind() const = 0;
        /**
         * @brief Unbinds the shader. Mostly for debug use.
         */
        virtual void Unbind() const = 0;

        /**
         * @brief Sets an integer uniform in the shader program.
         * @param name The name of the uniform variable.
         * @param value The integer value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformInt(const std::string& name, int value) = 0;
        /**
         * @brief Sets an array of integer uniforms in the shader program.
         * @param name The name of the uniform array variable.
         * @param values Pointer to the array of integer values.
         * @param count The number of elements in the array.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformIntArray(const std::string& name, int* values, uint32_t count) = 0;
        /**
         * @brief Sets a float uniform in the shader program.
         * @param name The name of the uniform variable.
         * @param value The float value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformFloat(const std::string& name, float value) = 0;
        /**
         * @brief Sets a 2D float vector uniform in the shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::vec2 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformFloat2(const std::string& name, const glm::vec2& value) = 0;
        /**
         * @brief Sets a 3D float vector uniform in the shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::vec3 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) = 0;
        /**
         * @brief Sets a 4D float vector uniform in the shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::vec4 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) = 0;
        /**
         * @brief Sets a 3x3 float matrix uniform in the shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::mat3 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
        /**
         * @brief Sets a 4x4 float matrix uniform in the shader program.
         * @param name The name of the uniform variable.
         * @param value The glm::mat4 value to set.
         *        Pure virtual function to be implemented by derived classes.
         */
        virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

        /**
         * @brief Gets the name of the shader.
         */
        inline const std::string& GetName() const { return m_Name; }

        /**
         * @brief Creates the shader instance according to the current Renderer API.
         */
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        /**
         * @brief Creates the shader instance according to the current Renderer API.
         */
        static Ref<Shader> Create(const std::string& filepath);

    protected:
        std::string m_Name;
    };
}
