#pragma once
#include "math/rect.h"
#include "math/vec4.h"

#include "SpriteBatch.h"

#include <memory>

namespace ftec {

	class Sprite;
	class Texture;
	class Font;
	enum class FontAlign;

	class Graphics2D {
	protected:
		//White texture for white shading (thanks obama)
		std::shared_ptr<Texture> m_WhiteTexture;
		std::shared_ptr<Font> m_Font;

		//This has the current shader and the current texture.
		Material m_Material;

		rect2i m_ClippingRectangle;
		color32 m_Color;
		float m_LineWidth =1.f;

		SpriteBatch batch;

		FontAlign m_VAlign;
		FontAlign m_HAlign;
	public:
		int calls = 0;
	public:
		Graphics2D();
		~Graphics2D();

		void begin();
		void end();

		void drawRectangle(const rect2f& rectangle, bool fill);
		void drawCircle(const vec2f &center, float radius, bool fill);

		void drawString(const std::string &text, const vec2f &position);
		void drawSprite(const Sprite &sprite, const vec2f &position);
		void drawLine(const vec2f &start, const vec2f &end);

		void drawClear();

		//Set stuff
		void setClip(const rect2i &rectangle);
		void resetClip();
		void setColor(const color32 &color);
		void setShader(std::shared_ptr<Shader> shader);

		void setLineWidth(float width) { m_LineWidth = width; };

		//Font stuff
		void setVerticalAlign(FontAlign alignment) { m_VAlign = alignment; };
		void setHorizontalAlign(FontAlign alignment) { m_HAlign = alignment; };
		void setFont(std::shared_ptr<Font> font) { m_Font = font;}
		

		//Returns the current clipping area, as set by clip
		inline const rect2i &getClip() { return m_ClippingRectangle; }
		inline const color32 &getColor() { return m_Color; }
		inline std::shared_ptr<Shader> getShader() { return m_Material.m_Shader; }

	protected:
		void setTexture(std::shared_ptr<Texture> texture);
		void flush();
	};
}