#include "Shader.h"
#include "io/ioutils.h"
#include "logger/log.h"
#include <vector>

namespace ftec {
	
	Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char *vp = vertexSource.c_str();
		const char *fp = fragmentSource.c_str();

		glShaderSource(vertexShader, 1, &vp, NULL);
		glShaderSource(fragmentShader, 1, &fp, NULL);

		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		auto checkCompileError = [&](GLuint sh){
			GLint success = 0;
			glGetShaderiv(sh, GL_COMPILE_STATUS, &success);

			if (success == GL_FALSE) {
				LOG_ERROR("Shader failed to compile"); GLint maxLength = 0;
				glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> errorLog(maxLength);
				glGetShaderInfoLog(sh, maxLength, &maxLength, &errorLog[0]);

				const char *d = &errorLog[0];
				LOG_ERROR(d);
			}
			

		};

		checkCompileError(vertexShader);
		checkCompileError(fragmentShader);

		m_Program = glCreateProgram();
		glAttachShader(m_Program, vertexShader);
		glAttachShader(m_Program, fragmentShader);

		glBindAttribLocation(m_Program, SHADER_ATTRIBUTE_POSITION, SHADER_ATTRIBUTE_POSITION_NAME);
		glBindAttribLocation(m_Program, SHADER_ATTRIBUTE_NORMAL, SHADER_ATTRIBUTE_NORMAL_NAME);
		glBindAttribLocation(m_Program, SHADER_ATTRIBUTE_UV, SHADER_ATTRIBUTE_UV_NAME);
		glBindAttribLocation(m_Program, SHADER_ATTRIBUTE_COLOR, SHADER_ATTRIBUTE_COLOR_NAME);
		glBindAttribLocation(m_Program, SHADER_ATTRIBUTE_TANGENT, SHADER_ATTRIBUTE_TANGENT_NAME);
		glBindAttribLocation(m_Program, SHADER_ATTRIBUTE_INSTANCE_POSITION, SHADER_ATTRIBUTE_INSTANCE_POSITION_NAME);

		glBindFragDataLocation(m_Program, 0, SHADER_OUTPUT_COLOR_NAME);

		glLinkProgram(m_Program);

		auto checkLinkError = [&](GLuint program) {
			GLint isLinked = 0;
			glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

				//The maxLength includes the NULL character
				std::vector<GLchar> errorLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);

				const char *d = &errorLog[0];
				LOG_ERROR(d);
			}
		};
		checkLinkError(m_Program);

		glDetachShader(m_Program, vertexShader);
		glDetachShader(m_Program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_Program);
	}

	void Shader::use()
	{
		glUseProgram(m_Program);
	}

	void Shader::reset()
	{
		glUseProgram(0);
	}

	int Shader::getUniformLocation(const std::string &uniform)
	{
		return glGetUniformLocation(m_Program, uniform.c_str());
	}

	int Shader::getAttributeLocation(const std::string & attribute)
	{
		return glGetAttribLocation(m_Program, attribute.c_str());
	}

	void Shader::setUniform(int location, const mat4 &m)
	{
		glUniformMatrix4fv(location, 1, GL_TRUE, &m.elements[0]);
	}

	void Shader::setUniform(int location, const vec2f &v)
	{
		glUniform2f(location, v.x, v.y);
	}

	void Shader::setUniform(int location, const vec3f &v)
	{
		glUniform3f(location, v.x, v.y, v.z);
	}

	void Shader::setUniform(int location, const vec4f &v)
	{
		glUniform4f(location, v.x, v.y, v.z, v.w);
	}

	void Shader::setUniform(int location, float f)
	{
		glUniform1f(location, f);
	}

	void Shader::setUniform(int location, int i)
	{
		glUniform1i(location, i);
	}
	
	std::shared_ptr<Shader> ftec::Shader::load(const std::string & name)
	{
		auto vertexSource = IOUtils::fileToString(name + "_vertex.glsl");
		auto fragmentSource = IOUtils::fileToString(name + "_fragment.glsl");

		return std::make_shared<Shader>(vertexSource, fragmentSource);
	}
}
