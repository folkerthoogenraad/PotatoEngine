#include "Sprite.h"

#include "Texture.h"
#include "logger/log.h"

namespace ftec {
	Sprite::Sprite(std::shared_ptr<Texture> texture)
		: Sprite(texture, Rectanglef(0,0,(float) texture->getWidth(), (float) texture->getHeight()))
	{ }

	Sprite::Sprite(std::shared_ptr<Texture> texture, const Rectanglef & rectangle)
		: m_Texture(texture)
	{
		this->recalculateUVRectangle(rectangle);
		this->recalculateLocalBounds(rectangle);
	}

	void Sprite::recalculateUVRectangle(const Rectanglef &textureRectangle)
	{
		m_UVRectangle.x() = textureRectangle.x() / (float)m_Texture->getWidth();
		m_UVRectangle.y() = textureRectangle.y() / (float)m_Texture->getHeight();

		m_UVRectangle.width() = textureRectangle.width() / (float)m_Texture->getWidth();
		m_UVRectangle.height() = textureRectangle.height() / (float)m_Texture->getHeight();
	}

	void Sprite::recalculateLocalBounds(const Rectanglef &textureRectangle)
	{
		m_Offset.x = 0;
		m_Offset.y= 0;
		m_Size.width = textureRectangle.width();
		m_Size.height = textureRectangle.height();
	}
}
