#pragma once

#include "Inno/Render/VertexArray.h"

namespace Inno
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        /**
         * @brief Binds the OpenGL vertex array for rendering.
         */
        virtual void Bind() const override;

        /**
         * @brief Unbinds the OpenGL vertex array.
         */
        virtual void Unbind() const override;

        /**
         * @brief Adds a vertex buffer to the vertex array.
         *
         * @param vertexBuffer The vertex buffer to add.
         */
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

        /**
         * @brief Adds an index buffer to the vertex array.
         *
         * @param IndexBuffer The index buffer to add.
         */
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        /**
         * @brief Gets the vertex buffer list of this OpenGL vertex array.
         *
         */
        virtual const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override { return m_VertexBuffers; };

        /**
         * @brief Gets the index buffer of this OpenGL vertex array.
         *
         */
        virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; };

    private:
        uint32_t m_RendererID;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}

