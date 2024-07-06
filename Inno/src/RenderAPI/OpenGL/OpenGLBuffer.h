#pragma once

#include "Inno/Render/Buffer.h"

namespace Inno
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		/// <summary>
		/// Binds the vertex buffer for OpenGL rendering.
		/// </summary>
		virtual void Bind() const override;
		/// <summary>
		/// Unbinds the vertex buffer.
		/// </summary>
		virtual void Unbind() const override;

		/// <summary>
		/// Sets the buffer layout of this OpenGL vertex buffer.
		/// </summary>
		/// <param name="layout">The input buffer layout.</param>
		virtual inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		/// <summary>
		/// Gets the buffer layout used of this OpenGL vertex buffer.
		/// </summary>
		/// <returns>The buffer layout currently used.</returns>
		virtual inline const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		/// <summary>
		/// Binds the vertex buffer for OpenGL rendering.
		/// </summary>
		virtual void Bind() const override;
		/// <summary>
		/// Unbinds the vertex buffer.
		/// </summary>
		virtual void Unbind() const override;
		/// <summary>
		/// Gets the number of indices in this OpenGL index buffer.
		/// </summary>
		/// <returns> The number of indices.</returns>
		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}

