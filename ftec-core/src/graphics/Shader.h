#pragma once

#include "resources/ResourceManager.h"
#include "GL.h"
#include "math/math.h"

#define SHADER_ATTRIBUTE_POSITION 0
#define SHADER_ATTRIBUTE_NORMAL 1
#define SHADER_ATTRIBUTE_UV 2
#define SHADER_ATTRIBUTE_COLOR 3
#define SHADER_ATTRIBUTE_TANGENT 4
#define SHADER_ATTRIBUTE_INSTANCE_POSITION 5

#define SHADER_ATTRIBUTE_POSITION_NAME "position"
#define SHADER_ATTRIBUTE_NORMAL_NAME "normal"
#define SHADER_ATTRIBUTE_TANGENT_NAME "tangent"
#define SHADER_ATTRIBUTE_UV_NAME "uv"
#define SHADER_ATTRIBUTE_COLOR_NAME "color"
#define SHADER_ATTRIBUTE_INSTANCE_POSITION_NAME "instancePosition"

#define SHADER_OUTPUT_COLOR_NAME "FragColor"

#define SHADER_DEFAULT_NAME "DEFAULT_SHADER"

namespace ftec {
	class Shader : public ManagableResource {
	private:
		GLuint m_Program;
	public:
		Shader(const std::string &vertexSource, const std::string &fragmentShader);
		~Shader();

		void use();
		void reset();

		int getUniformLocation(const std::string &uniform);
		int getAttributeLocation(const std::string &attribute);

		void setUniform(int location, const mat4 &m);
		void setUniform(int location, const vec2f &v);
		void setUniform(int location, const vec3f &v);
		void setUniform(int location, const vec4f &v);
		void setUniform(int location, float f);
		void setUniform(int location, int i);

		static std::shared_ptr<Shader> load(const std::string &name);
	};
}