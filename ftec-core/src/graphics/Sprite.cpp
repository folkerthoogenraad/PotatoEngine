#include "Sprite.h"

#include "Texture.h"

namespace ftec {
	Sprite::Sprite(std::shared_ptr<Texture> texture)
		: Sprite(texture, rect2f(0,0,(float) texture->getWidth(), (float) texture->getHeight()))
	{ }

	Sprite::Sprite(std::shared_ptr<Texture> texture, const rect2f & rectangle)
		: m_Texture(texture), m_TextureRectangle(rectangle)
	{
		this->recalculateUVRectangle();
	}

	void Sprite::recalculateUVRectangle()
	{
		m_UVRectangle.x() = m_TextureRectangle.x() / (float)m_Texture->getWidth();
		m_UVRectangle.y() = m_TextureRectangle.y() / (float)m_Texture->getHeight();

		m_UVRectangle.width() = m_TextureRectangle.width() / (float)m_Texture->getWidth();
		m_UVRectangle.height() = m_TextureRectangle.height() / (float)m_Texture->getHeight();
	}
}
