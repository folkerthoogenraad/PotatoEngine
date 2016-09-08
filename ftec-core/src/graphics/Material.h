#pragma once
#include <memory>
#include "Shader.h"
#include "Texture.h"

namespace ftec {
	struct Material {
		std::shared_ptr<Texture> m_Texture;
		std::shared_ptr<Shader> m_Shader;
		
		Material(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader) : m_Texture(texture), m_Shader(shader){}
	};
}