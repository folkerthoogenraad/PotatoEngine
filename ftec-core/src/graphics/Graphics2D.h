#pragma once
#include "math/rect.h"
#include "math/vec4.h"
#include <memory>

namespace ftec {

	class Sprite;
	class Texture;

	class Graphics2D {
	protected:
		//White texture for white shading (thanks obama)
		std::shared_ptr<Texture> m_WhiteTexture;

		rect2i m_ClippingRectangle;
		color m_Color;
	public:
		void drawRectangle(const rect2f& rectangle, bool fill);
		void drawString(const std::string &text, const vec2f &position);
		void drawSprite(const Sprite &sprite, const vec2f &position);

		void drawClear();

		//Set stuff
		void setClip(const rect2i &rectangle);
		void setColor(const color &color);

		//Returns the current clipping area, as set by clip
		inline const rect2i &getClip() { return m_ClippingRectangle; };
		inline const color &getColor() { return m_Color; }

	protected:
		void flush();
	};
}