#pragma once

#include <string>

namespace Inno
{
	/// <summary>
	/// Abstract base class for representing a shader in a graphics application.
	/// </summary>
	class Shader
	{
	public:
		Shader(const std::string& name)
			: m_Name(name) {}
		virtual ~Shader() = default;

		/// <summary>
		/// Binds the shader for use in rendering.
		/// </summary>
		virtual void Bind() const = 0;
		/// <summary>
		/// Unbinds the shader. Mostly for debug use.
		/// </summary>
		virtual void Unbind() const = 0;

	protected:
		std::string m_Name;
	};
}
