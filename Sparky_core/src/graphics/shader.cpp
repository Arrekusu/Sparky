#include "shader.h"
#include "../utils/fileutils.h"

namespace sparky {	namespace graphics {
	Shader::Shader(const char* vertPath, const char* fragPath)
		: m_VertPath(vertPath), m_FragPath(fragPath)
	{
		m_ProgramId = load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramId);
	}

	void Shader::setUniform1f(const GLchar * name, const float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1iv(const GLchar * name, const int * value, int count)
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1i(const GLchar * name, const int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar * name, const maths::vec2 & vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar * name, const maths::vec3 & vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar * name, const maths::vec4 & vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar * name, const maths::mat4 & matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::enable() const
	{
		glUseProgram(m_ProgramId);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	GLuint Shader::load()
	{
		GLuint program = glCreateProgram();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = read_file(m_VertPath);
		std::string fragmentSourceString = read_file(m_FragPath);

		const char* vertShaderSource = vertSourceString.c_str();
		const char* fragmentShaderSource = fragmentSourceString.c_str();

		glShaderSource(vertexShader, 1, &vertShaderSource, NULL);
		glCompileShader(vertexShader);

		GLint result;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertexShader, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader!!" << std::endl << &error[0] << std::endl;

			glDeleteShader(vertexShader);
			return 0;
		}


		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragmentShader, length, &length, &error[0]);
			std::cout << "Failed to compile fragment shader!!" << std::endl << &error[0] << std::endl;

			glDeleteShader(fragmentShader);
			return 0;
		}

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}
	GLint Shader::getUniformLocation(const GLchar * name)
	{
		return glGetUniformLocation(m_ProgramId, name);
	}
} }
