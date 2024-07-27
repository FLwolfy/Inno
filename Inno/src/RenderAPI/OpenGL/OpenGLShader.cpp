#include "pch.h"
#include "OpenGLShader.h"

#include "Inno/Core/Log.h"
#include "Inno/Core/Core.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace Inno
{
	static GLenum GetGLShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		else if (type == "fragment")
		{
			return GL_FRAGMENT_SHADER;
		}
		else
		{
			INNO_CORE_ASSERT(false, "Unknown shader type!");
			return 0;
		}

	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: Shader(name), m_RendererID(0)
	{
		std::unordered_map <GLenum, std::string> shaderSrcs;
		shaderSrcs[GL_VERTEX_SHADER] = vertexSrc;
		shaderSrcs[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(shaderSrcs);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath, const std::string& name)
		: Shader(name), m_RendererID(0)
	{
		// Read File Name
		if (name == "")
		{
			auto lastSlash = filepath.find_last_of("/\\");
			lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
			auto lastDot = filepath.rfind('.');
			auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
			m_Name = filepath.substr(lastSlash, count);
		}

		// Read File
		std::string shaderSrc = ReadFile(filepath);

		if (shaderSrc != "")
		{
			auto shaderSrcs = SplitShaders(shaderSrc);
			Compile(shaderSrcs);
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			INNO_CORE_LOGERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::SplitShaders(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			INNO_CORE_ASSERT(eol != std::string::npos, "Syntax error");

			size_t begin = pos + typeTokenLength;
			size_t typeStart = source.find_first_not_of(" \t", begin);
			INNO_CORE_ASSERT(typeStart != std::string::npos && typeStart < eol, "Syntax error");

			size_t typeEnd = source.find_last_not_of(" \t", eol - 1);
			std::string type = source.substr(typeStart, typeEnd - typeStart + 1);

			INNO_CORE_ASSERT(GetGLShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			INNO_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);

			shaderSources[GetGLShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs)
	{
		/* COPY FROM https://www.khronos.org/opengl/wiki/Shader_Compilation PAGE EXAMPLE SECTION WITH SLIGHT MODIFICATIONS*/

		// Get a program object.
		GLuint program = glCreateProgram();

		// Record the shader IDs
		INNO_CORE_ASSERT(shaderSrcs.size() <= 2, "OpenGLShader takes 2 shaders once maximize.")
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;

		for (auto& keyValue : shaderSrcs)
		{
			GLenum type = keyValue.first;
			const std::string& source = keyValue.second;

			// Create an empty shader handle
			GLuint shader = glCreateShader(type);

			// Send the shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceGL = source.c_str();
			glShaderSource(shader, 1, &sourceGL, 0);

			// Compile the shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				INNO_CORE_LOGERROR("Shader Complilation Failed!");
				INNO_CORE_ASSERT(false, (const char*)infoLog.data());

				return;
			}

			// Attach our shader to our program
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex] = shader;
			glShaderIDIndex++;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Link our program
		glLinkProgram(program);

		// Now time to link them together into a program.
		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto glID : glShaderIDs)
			{
				glDeleteShader(glID);
			}

			// Use the infoLog as you see fit.
			INNO_CORE_LOGERROR("OpenGL Shader Link Failed!");
			INNO_CORE_ASSERT(false, "{0}", infoLog.data());

			return;
		}

		// Always detach shaders after a successful link.
		for (auto glID : glShaderIDs)
		{
			glDetachShader(program, glID);
		}

		// Set the RendererID to program
		m_RendererID = program;

	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}
