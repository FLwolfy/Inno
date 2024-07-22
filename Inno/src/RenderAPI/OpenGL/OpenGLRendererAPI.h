#pragma once

#include "Inno/Render/Renderer.h"

namespace Inno
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
        OpenGLRendererAPI();
        
        /**
         * @brief Sets the clear color for the OpenGL rendering.
         * @param color The color to set as the clear color.
         */
        virtual void SetClearColor(const glm::vec4& color) override;

        /**
         * @brief Clears the OpenGL rendering context.
         */
        virtual void Clear() override;

        /**
         * @brief Draws indexed geometry using the provided vertex array.
         * @param vertexArray The vertex array containing geometry data.
         */
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}


