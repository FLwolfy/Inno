#pragma once

#include "Inno/Render/Buffer.h"

namespace Inno
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
        friend class OpenGLVertexArray;
    public:
        /**
         * @brief Constructs a vertex buffer and initializes it with vertex data.
         *
         * @param vertices Pointer to the array of vertices.
         * @param size Size of the vertex data in bytes.
         */
        OpenGLVertexBuffer(float* vertices, uint32_t size);

        /**
         * @brief Destroys the vertex buffer.
         */
        ~OpenGLVertexBuffer();

        /**
         * @brief Binds the vertex buffer for OpenGL rendering.
         */
        virtual void Bind() const override;

        /**
         * @brief Unbinds the vertex buffer.
         */
        virtual void Unbind() const override;

        /**
         * @brief Sets the buffer layout of this OpenGL vertex buffer.
         *
         * @param layout The input buffer layout.
         */
        virtual inline void SetLayout(const BufferLayout& layout) override
        {
            if (isSetLayoutLocked)
            {
                INNO_CORE_ASSERT(false, "Cannot change the buffer layout of a vertex buffer binded to a vertex array!");
                return;
            }
            
            m_Layout = layout; 
        }

        /**
         * @brief Gets the buffer layout used of this OpenGL vertex buffer.
         *
         * @returns The buffer layout currently used.
         */
        virtual inline const BufferLayout& GetLayout() const override { return m_Layout; }

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
        bool isSetLayoutLocked = false;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        /**
         * @brief Constructs an index buffer and initializes it with indices.
         *
         * @param indices Pointer to the array of indices.
         * @param count Count of the elements in the indices.
         */
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

        /**
         * @brief Destroys the index buffer.
         */
        ~OpenGLIndexBuffer();

        /**
         * @brief Binds the index buffer for OpenGL rendering.
         */
        virtual void Bind() const override;

        /**
         * @brief Unbinds the index buffer.
         */
        virtual void Unbind() const override;

        /**
         * @brief Gets the number of indices in this OpenGL index buffer.
         *
         * @returns The number of indices.
         */
        virtual uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}
