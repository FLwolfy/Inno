#pragma once

#include "Inno/Render/Buffer.h"

namespace Inno
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		/// <summary>
		/// Binds the vertex array for rendering.
		/// </summary>
		virtual void Bind() const = 0;
		/// <summary>
		/// Unbinds the vertex array.
		/// </summary>
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) = 0;

		/// <summary>
		/// Creates an vertex array based on the current graphics API.
		/// </summary>
		/// <returns>A pointer to the created VertexArray instance.</returns>
		static VertexArray* Create();
	};
}
