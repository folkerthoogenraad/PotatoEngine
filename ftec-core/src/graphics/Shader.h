#pragma once

#include "resources/ResourceManager.h"
#include <GL/glew.h>
#include "math/math.h"

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
		void setUniform(int location, const vec2 &v);
		void setUniform(int location, const vec3 &v);
		void setUniform(int location, const vec4 &v);
		void setUniform(int location, float f);
		void setUniform(int location, int i);

		static std::shared_ptr<Shader> load(const std::string &name);
	};
}