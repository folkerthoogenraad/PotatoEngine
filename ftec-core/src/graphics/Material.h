#pragma once
#include <memory>

#include "Shader.h"
#include "Texture.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

namespace ftec {

	struct Material {
	public:
		virtual void prepare() const = 0;
	};
	
	struct Material2D : public Material {
		
		std::shared_ptr<Shader> m_Shader = nullptr; //This should be automatic
		std::shared_ptr<Texture> m_TextureMap = nullptr;

		void prepare() const;
	};

	struct PBRMaterial : public Material {
		std::shared_ptr<Shader> m_Shader = nullptr;//This should be automatic

		std::shared_ptr<Texture> m_TextureMap = nullptr;
		std::shared_ptr<Texture> m_NormalMap = nullptr;

		std::shared_ptr<Texture> m_MetallicMap = nullptr;
		std::shared_ptr<Texture> m_RoughnessMap = nullptr;

		Vector3f m_Albedo = Vector3f(1.0,1.0,1.0);
		Vector3f m_Specular = Vector3f(1.0, 1.0, 1.0);
		Vector2f m_Tiling = Vector2f(1.0, 1.0);

		//Deprecated, for obvious reasons
		float m_Bumpiness = 0.0f;
		float m_Roughness = 1.0f;
		float m_Metallicness = 0.0f;
		
		PBRMaterial() = default;
		PBRMaterial(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader) : m_TextureMap(texture), m_Shader(shader){}

		void prepare() const;
	};
}