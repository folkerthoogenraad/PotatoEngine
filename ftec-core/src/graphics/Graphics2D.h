#pragma once
#include "math/rect.h"
#include "math/vec4.h"

#include "SpriteBatch.h"

#include <memory>

namespace ftec {

	class Sprite;
	class Texture;
	class Font;

	class Graphics2D {
	protected:
		//White texture for white shading (thanks obama)
		std::shared_ptr<Texture> m_WhiteTexture;
		std::shared_ptr<Font> m_Font;

		//This has the current shader and the current texture.
		Material m_Material;

		rect2i m_ClippingRectangle;
		color32 m_Color;

		SpriteBatch batch;
	public:
		int calls = 0;
	public:
		Graphics2D();
		~Graphics2D();

		void drawRectangle(const rect2f& rectangle, bool fill);
		void drawString(const std::string &text, const vec2f &position);
		void drawSprite(const Sprite &sprite, const vec2f &position);

		void drawClear();

		//Set stuff
		void setClip(const rect2i &rectangle);
		void setColor(const color32 &color);
		void setShader(std::shared_ptr<Shader> shader);

		//Returns the current clipping area, as set by clip
		inline const rect2i &getClip() { return m_ClippingRectangle; }
		inline const color32 &getColor() { return m_Color; }
		inline std::shared_ptr<Shader> getShader() { return m_Material.m_Shader; }

	protected:
		void setTexture(std::shared_ptr<Texture> texture);
		void flush();
	};
}