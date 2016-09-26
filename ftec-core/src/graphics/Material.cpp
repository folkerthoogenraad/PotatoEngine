#include "Material.h"

namespace ftec {
	Material Material::empty = Material(nullptr, nullptr);

	void Material::release()
	{
		m_Texture.reset();
		m_Shader.reset();
	}
}
