#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "../maths/maths.h"

namespace sparky {  namespace graphics {
	class Shader {
	private:
		GLuint m_ProgramId;
		const char *m_VertPath, *m_FragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void setUniform1f(const GLchar* name, const float value);
		void setUniform1iv(const GLchar* name, const int* value, int count);
		void setUniform1i(const GLchar* name, const int value);
		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);

		void setUniformMat4(const GLchar* name, const maths::mat4& matrix);
		void enable() const;
		void disable() const;

	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);
	};
}  }