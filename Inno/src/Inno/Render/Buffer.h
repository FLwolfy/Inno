#pragma once

namespace Inno
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		/// <summary>
		/// Binds the vertex buffer for rendering.
		/// </summary>
		virtual void Bind() const = 0;
		/// <summary>
		/// Unbinds the vertex buffer.
		/// </summary>
		virtual void Unbind() const = 0;

		/// <summary>
		/// Creates an index vertex based on the current graphics API.
		/// </summary>
		/// <param name="vertices">Pointer to the array of vertices.</param>
		/// <param name="size">Size of the vertex data in bytes.</param>
		/// <returns>A pointer to the created VertexBuffer instance.</returns>
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		/// <summary>
		/// Binds the index/element buffer for rendering.
		/// </summary>
		virtual void Bind() const = 0;
		/// <summary>
		/// Unbinds the index/element buffer.
		/// </summary>
		virtual void Unbind() const = 0;
		/// <summary>
		/// Gets the number of indices in this index buffer.
		/// </summary>
		/// <returns> The number of indices.</returns>
		virtual uint32_t GetCount() const = 0;

		/// <summary>
		/// Creates an index/element buffer based on the current graphics API.
		/// </summary>
		/// <param name="indices">Pointer to the array of indices.</param>
		/// <param name="count">Count of the elements in the indices.</param>
		/// <returns>A pointer to the created IndexBuffer instance.</returns>
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}

