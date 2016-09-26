#include "Graphics2D.h"
#include "Renderer.h"

#include "Texture.h"
#include "Sprite.h"

namespace ftec {

	void Graphics2D::drawRectangle(const rect2f & rectangle, bool fill)
	{
	}
	void Graphics2D::drawString(const std::string & text, const vec2f & position)
	{
	}
	void Graphics2D::drawSprite(const Sprite & sprite, const vec2f & position)
	{
	}
	void Graphics2D::drawClear()
	{
	}
	void Graphics2D::setClip(const rect2i &rectangle)
	{
		flush();

		this->m_ClippingRectangle = rectangle;
	}

	void Graphics2D::setColor(const color32 & color)
	{
		//TODO find out what is more efficient
		//Adding 4 bytes per vertex of memory to copy
		//Or add a drawcall

		this->m_Color = color;
	}

	void Graphics2D::setShader(std::shared_ptr<Shader> shader)
	{
		m_Material.m_Shader = shader;
	}

	void Graphics2D::flush()
	{
		Renderer::clip(this->m_ClippingRectangle);
	}
}
