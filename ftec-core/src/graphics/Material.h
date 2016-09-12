#pragma once
#include <memory>
#include "Shader.h"
#include "Texture.h"

namespace ftec {
	struct Material {
		static Material empty;

		std::shared_ptr<Texture> m_Texture;
		std::shared_ptr<Shader> m_Shader;
		
		Material() : m_Texture(0), m_Shader(0){};
		Material(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader) : m_Texture(texture), m_Shader(shader){}

		bool operator==(const Material &right) {
			return m_Texture == right.m_Texture && m_Shader == right.m_Shader;
		}
		bool operator!=(const Material &right) {
			return !(*this == right);
		}
	};
}