#pragma once

#include "Inno/Render/Buffer.h"

namespace Inno
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        /**
         * @brief Binds the vertex array for rendering.
         */
        virtual void Bind() const = 0;

        /**
         * @brief Unbinds the vertex array.
         */
        virtual void Unbind() const = 0;

        /**
         * @brief Adds a vertex buffer to the vertex array.
         *
         * @param vertexBuffer The vertex buffer to add.
         */
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;

        /**
         * @brief Adds an index buffer to the vertex array.
         *
         * @param IndexBuffer The index buffer to add.
         */
        virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) = 0;

        /**
         * @brief Creates a vertex array based on the current graphics API.
         *
         * @returns A pointer to the created VertexArray instance.
         */
        static VertexArray* Create();
    };

} 
