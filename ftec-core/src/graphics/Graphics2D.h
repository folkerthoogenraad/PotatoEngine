#pragma once
#include "math/line2.h"
#include "math/rect.h"
#include "math/circle.h"

#include "SpriteBatch.h"

#include <memory>

namespace ftec {

	class Sprite;
	class Texture;
	class Font;
	enum class FontAlign;

	class Graphics2D {
	public:
		enum class PointType {
			RECTANGLE, CIRCLE
		};
	protected:
		//White texture for white shading (thanks obama)
		std::shared_ptr<Texture> m_WhiteTexture;
		std::shared_ptr<Font> m_Font;

		//This has the current shader and the current texture.
		std::shared_ptr<Material2D> m_Material;

		recti m_ClippingRectangle;
		color32 m_Color;
		float m_LineWidth = 1.f;
		float m_PointSize = 2.f;
		PointType m_PointType = PointType::RECTANGLE;
		int m_CirclePrecision = 64;

		SpriteBatch batch;
		bool drawing3D = false;

		FontAlign m_VAlign;
		FontAlign m_HAlign;
	public:
		int calls = 0;//TODO is this needed?
	public:
		Graphics2D();
		~Graphics2D();

		void begin();
		void end();

		//Deprecated as fuck
		void begin3D(recti rectangle);
		void end3D();

		void drawRectangle(const rectf& rectangle, bool fill);
		void drawCircle(const vec2f &center, float radius, bool fill);
		void drawCircle(const circlef &circle, bool fill);
		void drawArc(const vec2f &center, float radius, bool fill, float startAngle, float angleLength);

		void drawString(const std::string &text, const vec2f &position);
		void drawSprite(const Sprite &sprite, const vec2f &position);
		void drawLine(const vec2f &start, const vec2f &end);
		void drawLine(const line2f &line);
		void drawPoint(const vec2f &point);

		void drawPrimitiveBegin(Primitive primitive);
		void drawPrimitiveSetTexture(std::shared_ptr<Texture> texture);
		void drawPrimitiveVertex(vec2f &vertex);
		void drawPrimitiveUV(vec2f &uv);
		void drawPrimitiveColor(color32 &color);
		void drawPrimitiveEnd();

		void drawClear();

		//Set stuff
		void setClip(const recti &rectangle);
		void resetClip();
		void setColor(const color32 &color);
		void setShader(std::shared_ptr<Shader> shader);

		void setDepth(float depth);

		void setLineWidth(float width) { m_LineWidth = width; }
		void setPointSize(float size) { m_PointSize = size; }
		void setPointType(PointType type) { m_PointType = type; }
		void setCirclePrecision(int subs) { m_CirclePrecision = subs; };

		//Font stuff
		void setVerticalAlign(FontAlign alignment) { m_VAlign = alignment; };
		void setHorizontalAlign(FontAlign alignment) { m_HAlign = alignment; };
		void setFont(std::shared_ptr<Font> font) { m_Font = font;}
		

		//Returns the current clipping area, as set by clip
		inline const recti &getClip() { return m_ClippingRectangle; }
		inline const color32 &getColor() { return m_Color; }
		inline std::shared_ptr<Shader> getShader() { return m_Material->m_Shader; } //TODO see implementation of setShader

	protected:
		void setTexture(std::shared_ptr<Texture> texture);
		void flush();
	};
}