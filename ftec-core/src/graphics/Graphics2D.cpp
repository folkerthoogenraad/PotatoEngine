#include "Graphics2D.h"
#include "Renderer.h"
#include "GraphicsState.h"

#include "Texture.h"
#include "Sprite.h"
#include "engine/Engine.h"
#include "Font.h"

namespace ftec {

	Graphics2D::Graphics2D()
	{
		m_WhiteTexture = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
		m_Material.m_Texture = m_WhiteTexture;
		m_Material.m_Shader = Engine::getResourceManager().load<Shader>("shaders/default2d");
		m_ClippingRectangle.width() = Engine::getWindow().getWidth();
		m_ClippingRectangle.height() = Engine::getWindow().getHeight();
		m_Color = color32(255, 255, 255, 255);
		batch.begin(Primitive::QUADS);

	}

	Graphics2D::~Graphics2D()
	{
		flush();
		batch.end();
		//LOG("Graphics2D drawcalls:" << calls);
	}

	void Graphics2D::drawRectangle(const rect2f & rectangle, bool fill)
	{
		setTexture(m_WhiteTexture);

		batch.color(m_Color);
		batch.vertex(vec3f(rectangle.left(), rectangle.top()));
		batch.vertex(vec3f(rectangle.right(), rectangle.top()));
		batch.vertex(vec3f(rectangle.right(), rectangle.bottom()));
		batch.vertex(vec3f(rectangle.left(), rectangle.bottom()));
	}

	void Graphics2D::drawString(const std::string & text, const vec2f & position)
	{
		vec2f currentPosition = position;

		auto f = Engine::getResourceManager().load<Font>("fonts/default14.fnt");

		for (char c : text) {
			//This should be done with a has, and then a reference get, that throws an exception when the character does not exist in the font.
			FontCharacter *fontCharacter = f->getCharacter(c);
			if (fontCharacter) {
				drawSprite(*fontCharacter->sprite, currentPosition);
				currentPosition.x += fontCharacter->xadvance;
			}
		}
	}

	void Graphics2D::drawSprite(const Sprite & sprite, const vec2f & position)
	{
		setTexture(sprite.m_Texture);

		batch.color(m_Color);
		batch.uv(vec2f(sprite.m_UVRectangle.left(), sprite.m_UVRectangle.top()));
		batch.vertex(vec3f(sprite.m_LocalBounds.left() + position.x, sprite.m_LocalBounds.top() + position.y));
		batch.uv(vec2f(sprite.m_UVRectangle.right(), sprite.m_UVRectangle.top()));
		batch.vertex(vec3f(sprite.m_LocalBounds.right() + position.x, sprite.m_LocalBounds.top() + position.y));
		batch.uv(vec2f(sprite.m_UVRectangle.right(), sprite.m_UVRectangle.bottom()));
		batch.vertex(vec3f(sprite.m_LocalBounds.right() + position.x, sprite.m_LocalBounds.bottom() + position.y));
		batch.uv(vec2f(sprite.m_UVRectangle.left(), sprite.m_UVRectangle.bottom()));
		batch.vertex(vec3f(sprite.m_LocalBounds.left() + position.x, sprite.m_LocalBounds.bottom() + position.y));
	}

	void Graphics2D::drawClear()
	{
		//TODO all the clipping and stuff?
		flush();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		if (shader != m_Material.m_Shader) {
			flush();
			m_Material.m_Shader = shader;
		}
	}

	void Graphics2D::setTexture(std::shared_ptr<Texture> texture)
	{
		if (texture != m_Material.m_Texture) {
			flush();
			m_Material.m_Texture = texture;
		}
	}

	void Graphics2D::flush()
	{
		if (batch.count() <= 0) {
			return;
		}

		calls++;

		Renderer::clip(this->m_ClippingRectangle);

		GraphicsState::m_TextureEnabled = true;
		GraphicsState::m_Shader = m_Material.m_Shader;
		GraphicsState::m_Textures[0].enabled = true;
		GraphicsState::m_Textures[0].texture = m_Material.m_Texture;// Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_CHECKERBOARD);

		GraphicsState::matrixProjection = mat4::orthographic(0,Engine::getWindow().getWidth(), Engine::getWindow().getHeight(), 0, -100, 100);

		batch.end();
		batch.begin(Primitive::QUADS);
	}
}
