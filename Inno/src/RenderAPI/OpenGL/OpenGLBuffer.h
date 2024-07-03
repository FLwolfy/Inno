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

	private:
		uint32_t m_RendererID;
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

