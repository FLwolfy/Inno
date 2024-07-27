#pragma once

#include "Inno/Render/Texture.h"

#include <glad/glad.h>

namespace Inno
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const TextureProperties& properties);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		/**
		 * @brief Retrieves the OpenGL texture2D's properties.
		 */
		virtual const TextureProperties& GetProperties() const override { return m_Properties; }

		/**
		 * @brief Retrieves the width of the OpenGL texture2D (in pixels).
		 */
		virtual uint32_t GetWidth() const override { return m_Width; }
		/**
		 * @brief Retrieves the height of the OpenGL texture2D (in pixels).
		 */
		virtual uint32_t GetHeight() const override { return m_Height; }
		/**
		 * @brief Retrieves the file path of the texture.
		 */
		virtual const std::string& GetPath() const override { return m_Path; }

		/**
		 * @brief Sets the OpenGL texture data.
		 * @param data Pointer to the data to be set.
		 * @param size Size of the data in bytes.
		 */
		virtual void SetData(void* data, uint32_t size) override;
		/**
		 * @brief Binds the texture to a specific slot.
		 * @param slot The slot to bind the texture to (default is 0).
		 */
		virtual void BindSlot(uint32_t slot = 0) const override;
		/**
		 * @brief Checks if the texture is loaded.
		 * @return True if the texture is loaded, false otherwise.
		 */
		virtual bool IsLoaded() const override { return m_IsLoaded; }

	private:
		TextureProperties m_Properties; 

		std::string m_Path;
		bool m_IsLoaded = false;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}

