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


    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferProperties& properties);
        virtual ~OpenGLFrameBuffer();

        /**
         * @brief Binds the framebuffer for rendering.
         */
        virtual void Bind() const override;
        /**
         * @brief Unbinds the current framebuffer.
         */
        virtual void Unbind() const override;

        /**
         * @brief Resizes the framebuffer to the specified width and height.
         * @param width The new width of the framebuffer.
         * @param height The new height of the framebuffer.
         */
        virtual void Resize(uint32_t width, uint32_t height) override;
        /**
         * @brief Reads a pixel value from the specified attachment at the given coordinates.
         * @param attachmentIndex The index of the attachment to read from.
         * @param x The x-coordinate of the pixel to read.
         * @param y The y-coordinate of the pixel to read.
         * @return The value of the pixel at the specified coordinates.
         */
        virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

        /**
         * @brief Clears the specified attachment with the given value.
         * @param attachmentIndex The index of the attachment to clear.
         * @param value The value to clear the attachment with.
         */
        virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;
        /**
         * @brief Gets the renderer ID for the specified attachment.
         * @param index The index of the attachment to retrieve the ID for.
         * @return The renderer ID for the specified attachment.
         */
        virtual inline uint32_t GetAttachmentRendererID(uint32_t index = 0) const override { INNO_CORE_ASSERT(index < m_AttachmentIDs.size(), "Size out of Index!"); return m_AttachmentIDs[index]; }
        /**
         * @brief Gets the properties of the framebuffer.
         */
        virtual inline const FrameBufferProperties& GetProperties() const override { return m_Properties; };

    private:
        void Invalidate();

    private:
        uint32_t m_RendererID;
        uint32_t m_DepthAttachmentID = 0;

        std::vector<uint32_t> m_AttachmentIDs;
        std::vector<FrameBufferAttachmentProperties> m_AttachmentProps;

        FrameBufferAttachmentProperties m_DepthAttachmentProp = FrameBufferAttachmentFormat::None;
        FrameBufferProperties m_Properties;
    };
}
