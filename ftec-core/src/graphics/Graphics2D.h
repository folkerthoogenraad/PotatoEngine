#pragma once

#include "math/Line2.h"
#include "math/Circle.h"

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

		//Deprecated as fuck //Should be gone soon
		void begin3D(Rectanglei rectangle);
		void end3D();

		void drawRectangle(const Rectanglef& rectangle, bool fill);
		void drawCircle(const Vector2f &center, float radius, bool fill);
		void drawCircle(const Circlef &circle, bool fill);
		void drawArc(const Vector2f &center, float radius, bool fill, float startAngle, float angleLength);

		void drawString(const std::string &text, const Vector2f &position);
		void drawSprite(const Sprite &sprite, const Vector2f &position);
		void drawLine(const Vector2f &start, const Vector2f &end);
		void drawLine(const Line2f &line);
		void drawPoint(const Vector2f &point);

		void drawClear();

		//Set stuff
		void setColor(const Color32 &color);
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

		void setCamera(Camera camera);

		inline const Color32 &getColor() { return m_Color; }
		inline std::shared_ptr<Shader> getShader() { return m_Material->m_Shader; } //TODO see implementation of setShader

	protected:
		void setTexture(std::shared_ptr<Texture> texture);
		void flush();
	};
}