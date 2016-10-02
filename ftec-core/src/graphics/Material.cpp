#include "Material.h"

namespace ftec {

	void Material::release()
	{
		m_TextureMap.reset();
		m_Shader.reset();
	}
}
