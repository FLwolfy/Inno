#pragma once

namespace Inno
{
	enum class ImageFormat
	{
		None = 0,
		R8,
		RGB8,
		RGBA8,
		RGBA32F
	};

	class Texture
	{
	public:
		struct TextureProperties
		{
			uint32_t Width = 1;							/* The width of the texture in pixels. */
			uint32_t Height = 1;						/* The height of the texture in pixels. */
			ImageFormat Format = ImageFormat::RGBA8;	/* The format of the texture image. */
			bool GenerateMips = true;					/* Flag indicating whether to generate mipmaps. */
		};

	public:
		virtual ~Texture() = default;

        /**
         * @brief Retrieves the texture's properties.
         */
        virtual const TextureProperties& GetProperties() const = 0;

        /**
         * @brief Retrieves the width of the texture (in pixels).
         */
        virtual uint32_t GetWidth() const = 0;
        /**
         * @brief Retrieves the height of the texture (in pixels).
         */
        virtual uint32_t GetHeight() const = 0;
        /**
         * @brief Retrieves the file path of the texture.
         */
        virtual const std::string& GetPath() const = 0;

        /**
         * @brief Sets the texture data.
         * @param data Pointer to the data to be set.
         * @param size Size of the data in bytes.
         */
        virtual void SetData(void* data, uint32_t size) = 0;
        /**
         * @brief Binds the texture to a specific slot.
         * @param slot The slot to bind the texture to (default is 0).
         */
        virtual void BindSlot(uint32_t slot = 0) const = 0;

        /**
         * @brief Checks if the texture is loaded.
         * @return True if the texture is loaded, false otherwise.
         */
        virtual bool IsLoaded() const = 0;

	};

	class Texture2D : public Texture
	{
	public:
        /**
         * @brief Creates a 2D texture with the specified properties.
         * @param properties The texture properties of the texture.
         * @return A reference pointer to the created 2D texture.
         */
        static Ref<Texture2D> Create(const TextureProperties& properties);
        /**
         * @brief Creates a 2D texture from a file path.
         * @param path The file path of the texture.
         * @return A reference to the created 2D texture.
         */
        static Ref<Texture2D> Create(const std::string& path);
	};
}

