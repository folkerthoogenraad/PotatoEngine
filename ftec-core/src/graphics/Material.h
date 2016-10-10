#pragma once
#include <memory>
#include "Shader.h"
#include "Texture.h"

namespace ftec {
	struct Material {

		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<Texture> m_TextureMap;
		std::shared_ptr<Texture> m_NormalMap;

		std::shared_ptr<Texture> m_MetallicMap;
		std::shared_ptr<Texture> m_RoughnessMap;

		vec3f m_Albedo = vec3f(1.0,1.0,1.0);
		vec3f m_Specular = vec3f(1.0, 1.0, 1.0);
		vec2f m_Tiling = vec2f(1.0, 1.0);

		//Deprecated, for obvious reasons
		float m_Bumpiness = 0.0f;
		float m_Roughness = 1.0f;
		float m_Metallicness = 0.0f;
		
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