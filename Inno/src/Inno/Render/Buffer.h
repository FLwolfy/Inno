#pragma once

#include "Inno/Render/Shader.h"

namespace Inno
{
    /////////////////////////////////////////////////////////////
    //////////////////////* VERTEX BUFFER *//////////////////////
    /////////////////////////////////////////////////////////////

    /**
     * @brief Structure representing a single buffer element.
     */
    struct BufferElement
    {
        std::string Name;           ///< Name of the buffer element.
        ShaderDataType Type;        ///< Data type of the buffer element.
        uint32_t Size;              ///< Size of the buffer element.
        uint32_t Offset;            ///< Offset of the buffer element.
        bool Normalized;            ///< Whether the buffer element is normalized.

        /**
         * @brief Default constructor for BufferElement.
         */
        BufferElement() = default;

        /**
         * @brief Constructor for BufferElement.
         * @param type Data type of the buffer element.
         * @param name Name of the buffer element.
         * @param normalized Whether the buffer element is normalized.
         */
        BufferElement(const ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(GetShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

        /**
         * @brief Gets the component count of this buffer element.
         * @returns Component count of the buffer element.
         */
        uint32_t GetComponentCount() const
        {
            return GetShaderDataTypeComponentCount(Type);
        }
    };

    /**
     * @brief Class representing the layout of a buffer.
     */
    class BufferLayout
    {
    public:
        BufferLayout() = default;
        /**
         * @brief Constructor for BufferLayout.
         * @param elements List of buffer elements to initialize the layout.
         */
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_BufferElements(elements)
        {
            CalculateOffsetNStride();
        }

        /**
         * @brief Gets the buffer elements of this buffer layout.
         * @returns Vector array containing the buffer elements.
         */
        inline const std::vector<BufferElement>& GetElements() const { return m_BufferElements; }

        /**
         * @brief Gets the stride (size) of this buffer layout.
         * @returns The stride of this buffer layout.
         */
        inline const uint32_t GetStride() const { return m_Stride; }

        std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); }

    private:
        std::vector<BufferElement> m_BufferElements; /// Vector holding buffer elements.
        uint32_t m_Stride = 0; /// Stride (size) of the buffer layout.

    private:
        /**
         * @brief Calculates offsets and stride for each buffer element.
         */
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

        /**
         * @brief Binds the vertex buffer for rendering.
         */
        virtual void Bind() const = 0;
        /**
         * @brief Unbinds the vertex buffer.
         */
        virtual void Unbind() const = 0;

        /**
         * @brief Sets the buffer layout of the vertex buffer.
         * @param layout Input buffer layout.
         */
        virtual inline void SetLayout(const BufferLayout& layout) = 0;
        /**
         * @brief Gets the buffer layout used of this vertex buffer.
         * @returns The buffer layout currently used.
         */
        virtual inline const BufferLayout& GetLayout() const = 0;

        /**
         * @brief Creates a vertex buffer based on the current graphics API.
         * @param vertices Pointer to the array of vertices.
         * @param size Size of the vertex data in bytes.
         * @returns A shared pointer to the created VertexBuffer instance.
         */
        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
    };

    ////////////////////////////////////////////////////////////
    //////////////////////* INDEX BUFFER *//////////////////////
    ////////////////////////////////////////////////////////////

    class IndexBuffer
    {
    public:
        /**
         * @brief Destructor for IndexBuffer.
         */
        virtual ~IndexBuffer() = default;

        /**
         * @brief Binds the index/element buffer for rendering.
         */
        virtual void Bind() const = 0;

        /**
         * @brief Unbinds the index/element buffer.
         */
        virtual void Unbind() const = 0;

        /**
         * @brief Gets the number of indices in this index buffer.
         * @returns The number of indices.
         */
        virtual uint32_t GetCount() const = 0;

        /**
         * @brief Creates an index/element buffer based on the current graphics API.
         * @param indices Pointer to the array of indices.
         * @param count Count of the elements in the indices.
         * @returns A shared pointer to the created IndexBuffer instance.
         */
        static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    };

    ////////////////////////////////////////////////////////////
    //////////////////////* FRAME BUFFER *//////////////////////
    ////////////////////////////////////////////////////////////

    enum class FrameBufferAttachmentFormat
    {
        None = 0,

        // Color
        RGBA8,
        RED_INTEGER,

        // Depth/stencil
        DEPTH24STENCIL8,

        // Defaults
        Depth = DEPTH24STENCIL8
    };

    struct FrameBufferAttachmentProperties
    {
    public:
        FrameBufferAttachmentProperties() = default;
        FrameBufferAttachmentProperties(FrameBufferAttachmentFormat format)
            : AttachmentFormat(format) {}

    public:
        FrameBufferAttachmentFormat AttachmentFormat = FrameBufferAttachmentFormat::None;
    };

    struct FrameBufferProperties
    {
    public:
        uint32_t Width = 0;
        uint32_t Height = 0;
        uint32_t Samples = 1;

        std::vector<FrameBufferAttachmentProperties> AttachmentProps;

        bool SwapChainTarget = false;
    };

    class FrameBuffer
    {
    public:
        virtual ~FrameBuffer() = default;

        /**
         * @brief Binds the framebuffer for rendering.
         */
        virtual void Bind() const = 0;
        /**
         * @brief Unbinds the current framebuffer.
         */
        virtual void Unbind() const = 0;

        /**
         * @brief Resizes the framebuffer to the specified width and height.
         * @param width The new width of the framebuffer.
         * @param height The new height of the framebuffer.
         */
        virtual void Resize(uint32_t width, uint32_t height) = 0;
        /**
         * @brief Reads a pixel value from the specified attachment at the given coordinates.
         * @param attachmentIndex The index of the attachment to read from.
         * @param x The x-coordinate of the pixel to read.
         * @param y The y-coordinate of the pixel to read.
         * @return The value of the pixel at the specified coordinates.
         */
        virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

        /**
         * @brief Clears the specified attachment with the given value.
         * @param attachmentIndex The index of the attachment to clear.
         * @param value The value to clear the attachment with.
         */
        virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;
        /**
         * @brief Gets the renderer ID for the specified attachment.
         * @param index The index of the attachment to retrieve the ID for.
         * @return The renderer ID for the specified attachment.
         */
        virtual inline uint32_t GetAttachmentRendererID(uint32_t index = 0) const = 0;
        /**
         * @brief Gets the properties of the framebuffer.
         */
        virtual inline const FrameBufferProperties& GetProperties() const = 0;

        /**
         * @brief Creates a new window with the specified properties according to the Window Render API.
         * @return A pointer to the newly created Window object.
         */
        static Ref<FrameBuffer> Create(FrameBufferProperties properties);
    };
}
