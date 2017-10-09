#pragma once

#include "math/Line2.h"
#include "math/Circle.h"
#include "math/Matrix3.h"
#include "math/Curve.h"

#include "SpriteBatch.h"	//For spritebatch
#include "Material.h"		//TODO remove this
#include "Camera.h"			//For camera

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
		Camera m_Camera;
	protected:
		//White texture for white shading (thanks obama)
		std::shared_ptr<Texture> m_WhiteTexture;
		std::shared_ptr<Font> m_Font;

		//This has the current shader and the current texture.
		std::shared_ptr<Material2D> m_Material;

		Color32 m_Color;
		float m_LineWidth = 1.f;
		float m_PointSize = 2.f;
		PointType m_PointType = PointType::RECTANGLE;
		int m_CirclePrecision = 16;

		int m_CurrentTextureIndex = 0;

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

		//Deprecated as fuck //Should be gone soon
		void begin3D(Rectanglei rectangle);
		void end3D();

		void drawRectangle(const Rectanglef& rectangle, bool fill);
		void drawCircle(const Vector2f &center, float radius, bool fill);
		void drawCircle(const Circlef &circle, bool fill);
		void drawArc(const Vector2f &center, float radius, bool fill, float startAngle, float angleLength);
		
		void drawBezier(const curves::VCubicBezier &bezier);
		void drawAutoBezier(const Vector2f &from, const Vector2f &to);

		void drawString(const std::string &text, const Vector2f &position);

		void drawSprite(const Sprite &sprite, Vector2f position);
		void drawSprite(const Sprite &sprite, Rectanglef rectangle);
		void drawSprite(const Sprite &sprite, Vector2f position, Vector2f scale, float rotation);
		
		void drawLine(const Vector2f &start, const Vector2f &end);
		void drawLine(const Line2f &line);
		void drawPoint(const Vector2f &point);

		void drawClear();

		//Set stuff
		void setColor(const Color32 &color);

		void setDepth(float depth);

		void setLineWidth(float width) { m_LineWidth = width; }
		void setPointSize(float size) { m_PointSize = size; }
		void setPointType(PointType type) { m_PointType = type; }
		void setCirclePrecision(int subs) { m_CirclePrecision = subs; };

		//Font stuff
		void setVerticalAlign(FontAlign alignment) { m_VAlign = alignment; };
		void setHorizontalAlign(FontAlign alignment) { m_HAlign = alignment; };
		void setFont(std::shared_ptr<Font> font) { m_Font = font;}

		void setCamera(Camera camera);

		std::shared_ptr<Texture> getWhiteTexture() const { return m_WhiteTexture; }

		inline const Color32 &getColor() { return m_Color; }
	protected:
		void setTexture(std::shared_ptr<Texture> texture);
		void flush();
	};
}