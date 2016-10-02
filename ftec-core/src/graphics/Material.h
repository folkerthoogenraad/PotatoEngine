#pragma once
#include <memory>
#include "Shader.h"
#include "Texture.h"

namespace ftec {
	struct Material {

		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<Texture> m_TextureMap;
		std::shared_ptr<Texture> m_NormalMap;

		
		Material() : m_TextureMap(0), m_Shader(0){};
		Material(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader) : m_TextureMap(texture), m_Shader(shader){}

		bool operator==(const Material &right) {
			return m_TextureMap == right.m_TextureMap && m_Shader == right.m_Shader;
		}
		bool operator!=(const Material &right) {
			return !(*this == right);
		}

		//Releases the two resources so that they can get cleaned up
		void release();
	};
}