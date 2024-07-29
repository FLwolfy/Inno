#include "pch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Inno
{
	/////////////////////////////////////////////////////////////
	//////////////////////* VERTEX BUFFER *//////////////////////
	/////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	////////////////////////////////////////////////////////////
	//////////////////////* INTEX BUFFER *//////////////////////
	////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	////////////////////////////////////////////////////////////
	//////////////////////* FRAME BUFFER *//////////////////////
	////////////////////////////////////////////////////////////

	static const uint32_t s_MaxFrameBufferSize = 8192;

	static void AttachAttachment(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
	{
		bool isMultisampled = samples > 1;
		if (isMultisampled)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		GLenum AttachmentTarget = isMultisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, AttachmentTarget, id, 0);
	}

	static void AttachDepthAttachment(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
	{
		bool isMultisampled = samples > 1;
		if (isMultisampled)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else
		{
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		GLenum AttachmentTarget = isMultisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, AttachmentTarget, id, 0);
	}

	static bool IsDepthFormat(FrameBufferAttachmentFormat format)
	{
		switch (format)
		{
			case FrameBufferAttachmentFormat::DEPTH24STENCIL8:  return true;
		}

		return false;
	}

	static GLenum FBAttachmentFormatToGL(FrameBufferAttachmentFormat format)
	{
		switch (format)
		{
			case FrameBufferAttachmentFormat::RGBA8:       return GL_RGBA8;
			case FrameBufferAttachmentFormat::RED_INTEGER: return GL_RED_INTEGER;
		}

		INNO_CORE_ASSERT(false, "Unknown texture/attachment format!");
		return 0;
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferProperties& properties)
		: m_Properties(properties)
	{
		for (auto prop : m_Properties.AttachmentProps)
		{
			if (!IsDepthFormat(prop.AttachmentFormat))
				m_AttachmentProps.emplace_back(prop);
			else
				m_DepthAttachmentProp = prop;
		}

		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(static_cast<GLsizei>(m_AttachmentIDs.size()), m_AttachmentIDs.data());
		glDeleteTextures(1, &m_DepthAttachmentID);
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(static_cast<GLsizei>(m_AttachmentIDs.size()), m_AttachmentIDs.data());
			glDeleteTextures(1, &m_DepthAttachmentID);

			m_AttachmentIDs.clear();
			m_DepthAttachmentID = 0;
		}

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool isMultisampled = m_Properties.Samples > 1;
		GLenum AttachmentTarget = isMultisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;

		// Attachments
		if (m_AttachmentProps.size())
		{
			// Create Attachments
			m_AttachmentIDs.resize(m_AttachmentProps.size());
			glCreateTextures(AttachmentTarget, static_cast<GLsizei>(m_AttachmentIDs.size()), m_AttachmentIDs.data());

			for (size_t i = 0; i < m_AttachmentIDs.size(); i++)
			{
				// Bind Attachments
				glBindTexture(AttachmentTarget, m_AttachmentIDs[i]);

				switch (m_AttachmentProps[i].AttachmentFormat)
				{
					case FrameBufferAttachmentFormat::RGBA8:
						AttachAttachment(m_AttachmentIDs[i], m_Properties.Samples, GL_RGBA8, GL_RGBA, m_Properties.Width, m_Properties.Height, static_cast<int>(i));
						break;
					case FrameBufferAttachmentFormat::RED_INTEGER:
						AttachAttachment(m_AttachmentIDs[i], m_Properties.Samples, GL_R32I, GL_RED_INTEGER, m_Properties.Width, m_Properties.Height, static_cast<int>(i));
						break;
				}
			}
		}

		if (m_DepthAttachmentProp.AttachmentFormat != FrameBufferAttachmentFormat::None)
		{
			// Create and Bind Attachments
			glCreateTextures(AttachmentTarget, 1, &m_DepthAttachmentID);
			glBindTexture(AttachmentTarget, m_DepthAttachmentID);

			switch (m_DepthAttachmentProp.AttachmentFormat)
			{
				case FrameBufferAttachmentFormat::DEPTH24STENCIL8:
					AttachDepthAttachment(m_DepthAttachmentID, m_Properties.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Properties.Width, m_Properties.Height);
					break;
			}
		}

		if (m_AttachmentIDs.size() > 1)
		{
			INNO_CORE_ASSERT(m_AttachmentIDs.size() <= 4, "Attachment out of range!");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(static_cast<GLsizei>(m_AttachmentIDs.size()), buffers);
		}
		else if (m_AttachmentIDs.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

		INNO_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Properties.Width, m_Properties.Height);
	}

	void OpenGLFrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFrameBufferSize || height > s_MaxFrameBufferSize)
		{
			INNO_CORE_LOGWARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_Properties.Width = width;
		m_Properties.Height = height;

		Invalidate();
	}

	int OpenGLFrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		INNO_CORE_ASSERT(attachmentIndex < m_AttachmentIDs.size(), "Index out of range!");

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	void OpenGLFrameBuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		INNO_CORE_ASSERT(attachmentIndex < m_AttachmentIDs.size(), "Index out of range!");

		auto& prop = m_AttachmentProps[attachmentIndex];
		glClearTexImage(m_AttachmentIDs[attachmentIndex], 0, FBAttachmentFormatToGL(prop.AttachmentFormat), GL_INT, &value);
	}

}
