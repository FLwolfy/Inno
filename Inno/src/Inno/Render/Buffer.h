#pragma once

#include "Inno/Render/Shader.h"

namespace Inno
{
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() = default;
		BufferElement(const ShaderDataType type, std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(GetShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		/// <summary>
		/// Gets the component count of this buffer element.
		/// </summary>
		uint32_t GetComponentCount() const
		{
			return GetShaderDataTypeComponentCount(Type);
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_BufferElements(elements)
		{
			CalculateOffsetNStride();
		}

		/// <summary>
		/// Gets the buffer elements of this buffer layout
		/// </summary>
		/// <returns>The vector array containing the buffer elements.</returns>
		inline const std::vector<BufferElement>& GetElements() const { return m_BufferElements; }
		/// <summary>
		/// Gets the stride (count size) of this buffer layout.
		/// </summary>
		/// <returns>The stride of this buffer layout.</returns>
		inline const uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }		
		std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); }

	private:
		std::vector<BufferElement> m_BufferElements;
		uint32_t m_Stride = 0;

	private:
		void CalculateOffsetNStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;

			for (auto& element : m_BufferElements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	};

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
		/// Sets the buffer layout of the vertex buffer.
		/// </summary>
		/// <param name="layout">The input buffer layout.</param>
		virtual inline void SetLayout(const BufferLayout& layout) = 0;
		/// <summary>
		/// Gets the buffer layout used of this vertex buffer.
		/// </summary>
		/// <returns>The buffer layout currently used.</returns>
		virtual inline const BufferLayout& GetLayout() const = 0;

		/// <summary>
		/// Creates an vertex buffer based on the current graphics API.
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

