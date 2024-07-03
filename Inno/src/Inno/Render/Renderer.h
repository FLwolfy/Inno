#pragma once

namespace Inno
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		/// <summary>
		/// Gets the Render API currently used.
		/// </summary>
		/// <returns> The current Render API.</returns>
		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:
		static RendererAPI s_RendererAPI;
	};
}
