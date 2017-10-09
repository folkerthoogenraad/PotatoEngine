#include "Sprite.h"

#include "Texture.h"
#include "logger/log.h"

#define FLIPPED_Y false

namespace ftec {
	Sprite::Sprite(std::shared_ptr<Texture> texture)
		: Sprite(texture, 
			texture ?
			Rectanglef(0, 0, (float)texture->getWidth(), (float)texture->getHeight()) :
			Rectanglef(0, 0, 1, 1))
	{ }

	Sprite::Sprite(std::shared_ptr<Texture> texture, const Rectanglef & rectangle)
		: m_Texture(texture)
	{
		this->recalculateUVRectangle(rectangle);
		this->recalculateLocalBounds(rectangle);
	}

	Sprite &Sprite::flipY()
	{
		m_UVRectangle.position.y += m_UVRectangle.size.y;
		m_UVRectangle.size.y = -m_UVRectangle.size.y;
		return *this;
	}

	void Sprite::recalculateUVRectangle(const Rectanglef &textureRectangle)
	{
		if (m_Texture) {
			m_UVRectangle.x() = textureRectangle.x() / (float)m_Texture->getWidth();
			m_UVRectangle.y() = textureRectangle.y() / (float)m_Texture->getHeight();

			m_UVRectangle.width() = textureRectangle.width() / (float)m_Texture->getWidth();
			m_UVRectangle.height() = textureRectangle.height() / (float)m_Texture->getHeight();
		}
		else {
			m_UVRectangle = Rectanglef(0, 0, 1, 1);
		}
	}

	void Sprite::recalculateLocalBounds(const Rectanglef &textureRectangle)
	{
		m_Offset.x = 0;
		m_Offset.y= 0;
		m_Size.width = textureRectangle.width();
		m_Size.height = textureRectangle.height();
	}

	SpriteSlices::SpriteSlices()
		: SpriteSlices(0,0,0,0)
	{ }

	SpriteSlices::SpriteSlices(float top, float bottom, float left, float right)
		:top(top), bottom(bottom), left(left), right(right)
	{
	}
}
