#pragma once

#include <string>

#include "Inno/Render/Shader.h"

namespace Inno
{
	class OpenGLShader : public Shader
	{
	public:
		/// <summary>
		/// Constructs an OpenGLShader with the specified name, vertex source, and fragment source.
		/// </summary>
		/// <param name="name">The name of the shader.</param>
		/// <param name="vertexSrc">The vertex shader source code.</param>
		/// <param name="fragmentSrc">The fragment shader source code.</param>
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		/// <summary>
		/// Binds the shader for use in rendering.
		/// </summary>
		virtual void Bind() const override;
		/// <summary>
		/// Unbinds the shader. Mostly for debug use.
		/// </summary>
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererID;
	};
}

