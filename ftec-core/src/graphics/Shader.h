#pragma once

#include "resources/ManageableResource.h"
#include <memory>
#include <string>

#define SHADER_ATTRIBUTE_POSITION 0
#define SHADER_ATTRIBUTE_NORMAL 1
#define SHADER_ATTRIBUTE_UV 2
#define SHADER_ATTRIBUTE_COLOR 3
#define SHADER_ATTRIBUTE_TANGENT 4
#define SHADER_ATTRIBUTE_INSTANCE_POSITION 5

#define SHADER_ATTRIBUTE_TEXTURE_INDEX 10

#define SHADER_ATTRIBUTE_POSITION_NAME "position"
#define SHADER_ATTRIBUTE_NORMAL_NAME "normal"
#define SHADER_ATTRIBUTE_TANGENT_NAME "tangent"
#define SHADER_ATTRIBUTE_UV_NAME "uv"
#define SHADER_ATTRIBUTE_COLOR_NAME "color"
#define SHADER_ATTRIBUTE_INSTANCE_POSITION_NAME "instancePosition"
#define SHADER_ATTRIBUTE_TEXTURE_INDEX_NAME "textureIndex"

#define SHADER_OUTPUT_COLOR_NAME "FragColor"

#define SHADER_DEFAULT_NAME "DEFAULT_SHADER"

namespace ftec {

	template<typename T> struct Matrix4; typedef Matrix4<float> Matrix4f;
	template<typename T> struct Vector2; typedef Vector2<float> Vector2f;
	template<typename T> struct Vector3; typedef Vector3<float> Vector3f;
	template<typename T> struct Vector4; typedef Vector4<float> Vector4f;

	class Shader : public ManageableResource {
	protected:
		unsigned int m_Program;
	public:
		Shader(const std::string &vertexSource, const std::string &fragmentShader);
		~Shader();

		void use();
		void reset();

		int getUniformLocation(const std::string &uniform);
		int getAttributeLocation(const std::string &attribute);

		void setUniform(int location, const Matrix4f &m);
		void setUniform(int location, const Vector2f &v);
		void setUniform(int location, const Vector3f &v);
		void setUniform(int location, const Vector4f &v);
		void setUniform(int location, float f);
		void setUniform(int location, int i);
		void setUniform(int location, unsigned int i);

		static std::shared_ptr<Shader> load(const std::string &name);
	protected:
		virtual void init();

	};
}