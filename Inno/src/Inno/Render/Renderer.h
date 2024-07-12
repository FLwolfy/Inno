#pragma once

#include "Inno/Render/RendererAPI.h"
#include "Inno/Render/Camera.h"
#include "Inno/Render/Shader.h"

namespace Inno
{
    class Renderer
    {
    public:
        class Command
        {
        public:
            /**
             * @brief Sets the clear color for rendering.
             * @param color The color to set as the clear color.
             */
            static inline void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
            /**
             * @brief Clears the current rendering context.
             */
            static inline void Clear() { s_RendererAPI->Clear(); }
            /**
             * @brief Retrieves the current rendering API.
             * @return The current rendering API.
             */
            static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
            /**
             * @brief Sets the current rendering API.
             */
            static void SetAPI(RendererAPI::API api);
        };

    public:
        /**
         * @brief Begins a new rendering scene with specified environment inputs.
         *        Every submit in this renderer scene should be in between the BeginScene() and EndScene();
         */
        static void BeginScene(Camera& camera);
        /**
         * @brief Ends the current rendering scene.
         *        Every submit in this renderer scene should be in between the BeginScene() and EndScene();
         */
        static void EndScene();
        /**
         * @brief Submits a vertex array for rendering with given shader.
         *        Every submit in this renderer scene should be in between the BeginScene() and EndScene();
         * @param vertexArray The vertex array to render.
         * @param shader The given shader.
         */
        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

    private:
        static SceneData* s_SceneData;
        static std::shared_ptr<RendererAPI> s_RendererAPI;
    };

}
