#pragma once

#include "Inno/Render/VertexArray.h"

#include <glm/glm.hpp>

namespace Inno
{
    class RendererAPI
    {
    public:
        /**
         * @brief Enumeration of supported rendering APIs.
         */
        enum class API
        {
            None = 0,   /* No specific rendering API selected. */
            OpenGL      /* OpenGL rendering API. */
        };

    public:
        virtual ~RendererAPI() = default;
       
        /**
         * @brief Sets the clear color for rendering.
         * @param color The color to set as the clear color.
         */
        virtual void SetClearColor(const glm::vec4& color) = 0;
        /**
         * @brief Clears the current rendering context.
         */
        virtual void Clear() = 0;
        /**
         * @brief Draws indexed geometry using the provided vertex array.
         * @param vertexArray The vertex array containing geometry data.
         */
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
        /**
         * @brief Initializes the renderer settings for this specific renderer API.
         */
        virtual void Init() = 0;

        /**
         * @brief Retrieves the current rendering API.
         * @return The current rendering API.
         */
        static inline API GetAPI() { return s_API; }
        /**
         * @brief Sets the current rendering API.
         */
        static inline void SetAPI(API api) { s_API = api; }

        /**
         * @brief Creates a RendererAPI instance based on the current rendering API.
         * @return The shared pointer to the created RendererAPI instance.
         */
        static Unq<RendererAPI> Create();

	private:
        static API s_API;
	};
}

