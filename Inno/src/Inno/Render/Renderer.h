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
             * @brief Initializes the renderer settings.
             */
            static inline void Init() { s_RendererAPI->Init(); }
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
              * @brief Retrieves the shader library of the current rendering API.
              */
            static inline ShaderLibrary& GetShaderLibrary() { return s_ShaderLibrary; }
            /**
             * @brief Retrieves the current rendering API.
             */
            static inline const RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
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
         * @param shader The given shader.
         * @param vertexArray The vertex array to render.
         * @param transform The transform model matrix of the object.
         */
        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 transform);

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

    private:
        static Unq<SceneData> s_SceneData;
        static Unq<RendererAPI> s_RendererAPI;

        static ShaderLibrary s_ShaderLibrary;
    };

}
