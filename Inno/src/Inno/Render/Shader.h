#pragma once

#include <string>

#include "Inno/Core/Core.h"

namespace Inno
{
	/// <summary>
	/// The ShaderDataType used by Inno.
	/// </summary>
	enum class ShaderDataType
	{
		None = 0,
		Bool,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
		Mat3,
		Mat4
	};

	/// <summary>
	/// Returns the defined size of the input ShaderDataType.
	/// </summary>
	/// <param name="type">The input ShaderDataType</param>
	/// <returns>The defined size of the input ShaderDataType</returns>
	static uint32_t GetShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Bool:     return 1;
			case ShaderDataType::Float:	   return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;;
			case ShaderDataType::Int4:     return 4 * 4;;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown ShaderDataType '{0}'!", type);
				return 0;
			}
		}
	}

	/// <summary>
	/// Returns the defined component count of the input ShaderDataType.
	/// </summary>
	/// <param name="type">The input ShaderDataType</param>
	/// <returns>The defined component count of the input ShaderDataType.</returns>
	static uint32_t GetShaderDataTypeComponentCount(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Bool:     return 1;
			case ShaderDataType::Float:	   return 1;
			case ShaderDataType::Float2:   return 2;
			case ShaderDataType::Float3:   return 3;
			case ShaderDataType::Float4:   return 4;
			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;;
			case ShaderDataType::Int4:     return 4;;
			case ShaderDataType::Mat3:     return 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4;

			default:
			{
				INNO_CORE_ASSERT(false, "Unknown ShaderDataType '{0}'!", type);
				return 0;
			}
		}
	}

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
