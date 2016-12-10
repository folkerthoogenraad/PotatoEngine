#include "Graphics2D.h"
#include "Renderer.h"
#include "GraphicsState.h"
#include "Graphics.h"
#include "Window.h"

#include "Texture.h"
#include "Sprite.h"
#include "engine/Engine.h"
#include "Font.h"
#include "logger/log.h"

#include "engine/Time.h"

#include "GL.h"

#include "resources/ResourceManager.h"

namespace ftec {

	Graphics2D::Graphics2D()
	{
		m_WhiteTexture = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
		//m_Font = Engine::getResourceManager().load<Font>("fonts/default14.fnt");
		m_Font = Engine::getResourceManager().load<Font>("fonts/Ubuntu.ttf");

		m_VAlign = FontAlign::TOP;
		m_HAlign = FontAlign::LEFT;

		m_Material = std::make_shared<Material2D>();

		m_Material->m_TextureMap = m_WhiteTexture;
		m_Material->m_Shader = Engine::getResourceManager().load<Shader>("shaders/default2d");
		resetClip();
		m_Color = Color32(255, 255, 255, 255);
	}

	Graphics2D::~Graphics2D()
	{
		end();
	}

	void Graphics2D::begin() {
		batch.begin(Primitive::QUADS);
	}

	void Graphics2D::end() {
		if (batch.isDrawing()) {
			flush();
			batch.end();
		}
		calls = 0;
	}

	void Graphics2D::begin3D(recti rectangle)
	{
		drawing3D = true;
		flush();
		Renderer::renderport(rectangle);

		Graphics::begin();
	}

	void Graphics2D::end3D()
	{
		Graphics::end();
		//Clear the depth values from the 3D rendering
		glClear(GL_DEPTH_BUFFER_BIT);
		drawing3D = false;
		//flush();
	}

	void Graphics2D::drawRectangle(const rectf & rectangle, bool fill)
	{
		if (drawing3D) {
			LOG_ERROR("Can't draw 2D when drawing in 3D");
		}
		setTexture(m_WhiteTexture);

		batch.color(m_Color);
		if (fill) {
			batch.vertex(rectangle.topleft());
			batch.vertex(rectangle.bottomleft());
			batch.vertex(rectangle.bottomright());
			batch.vertex(rectangle.topright());
		}
		else {
			drawLine(rectangle.topleft(), rectangle.topright());
			drawLine(rectangle.bottomleft(), rectangle.topleft());
			drawLine(rectangle.bottomright(), rectangle.bottomleft());
			drawLine(rectangle.topright(), rectangle.bottomright());
		}
	}

	void Graphics2D::drawPrimitiveBegin(Primitive primitive)
	{
		if (batch.isDrawing())
			batch.end();

		batch.begin(primitive);
	}
	void Graphics2D::drawPrimitiveSetTexture(std::shared_ptr<Texture> texture)
	{
		setTexture(texture);
	}
	void Graphics2D::drawPrimitiveVertex(Vector2f & vertex)
	{
		batch.vertex(vertex);
	}
	void Graphics2D::drawPrimitiveUV(Vector2f & uv)
	{
		batch.uv(uv);
	}
	void Graphics2D::drawPrimitiveColor(Color32 & color)
	{
		batch.color(color);
	}
	void Graphics2D::drawPrimitiveEnd()
	{
		flush();
	}

	void Graphics2D::drawCircle(const Vector2f & center, float radius, bool fill)
	{
		if (drawing3D) {
			LOG_ERROR("Can't draw 2D when drawing in 3D");
		}

		drawArc(center, radius, fill, 0, PI * 2);
		/*if (fill) {
			setTexture(m_WhiteTexture);
			batch.color(m_Color);

			const float steps = 32;
			const float anglePerStep = 2 * PI / steps;
			for (float i = 0; i < steps; i += 2) {
				batch.vertex(center);

				batch.vertex(center + Vector3f(cosf(anglePerStep * (i + 2)), sinf(anglePerStep * (i + 2))) * radius);
				batch.vertex(center + Vector3f(cosf(anglePerStep * (i + 1)), sinf(anglePerStep * (i + 1))) * radius);
				batch.vertex(center + Vector3f(cosf(anglePerStep * (i + 0)), sinf(anglePerStep * (i + 0))) * radius);
			}
		}
		else {
			//TODO
		}*/
	}

	void Graphics2D::drawCircle(const circlef & circle, bool fill)
	{
		drawCircle(circle.center, circle.radius, fill);
	}

	void Graphics2D::drawArc(const Vector2f & center, float radius, bool fill, float startAngle, float angleLength)
	{
		if (drawing3D) {
			LOG_ERROR("Can't draw 2D when drawing in 3D");
		}

		setTexture(m_WhiteTexture);
		batch.color(m_Color);

		const float steps = (float)m_CirclePrecision; //TODO make this dependend on the angleLimit
		const float anglePerStep = angleLength / steps;

		if (fill) {
			
			for (float i = 0; i < steps; i += 2) {

				batch.vertex(center);

				batch.vertex(center + Vector2f(cosf(startAngle + anglePerStep * (i + 2)), sinf(startAngle + anglePerStep * (i + 2))) * radius);
				batch.vertex(center + Vector2f(cosf(startAngle + anglePerStep * (i + 1)), sinf(startAngle + anglePerStep * (i + 1))) * radius);
				batch.vertex(center + Vector2f(cosf(startAngle + anglePerStep * (i + 0)), sinf(startAngle + anglePerStep * (i + 0))) * radius);
			}
		}
		else {
			for (float i = 0; i < steps; ++i) {
				drawLine(
					Vector2f(center + Vector2f(cosf(startAngle + anglePerStep * (i + 1)), sinf(startAngle + anglePerStep * (i + 1))) * radius),
					Vector2f(center + Vector2f(cosf(startAngle + anglePerStep * (i + 0)), sinf(startAngle + anglePerStep * (i + 0))) * radius)
				);
			}
		}
	}

	void Graphics2D::drawString(const std::string & text, const Vector2f & position)
	{
		if (drawing3D) {
			LOG_ERROR("Can't draw 2D when drawing in 3D");
		}
		Vector2f start = position;

		//TODO figure this out for each line, not for the complete string
		if (m_HAlign != FontAlign::LEFT || m_VAlign != FontAlign::TOP) {
			Vector2f bounds = m_Font->measure(text);
			
			if (m_HAlign == FontAlign::CENTER)
				start.x -= bounds.x / 2;

			if (m_HAlign == FontAlign::RIGHT)
				start.x -= bounds.x;

			if (m_VAlign == FontAlign::CENTER)
				start.y -= bounds.y / 2;

			if (m_VAlign == FontAlign::BOTTOM)
				start.y -= bounds.y;
		}


		Vector2f currentPosition = start;

		for (char c : text) {
			//This should be done with a has, and then a reference get, that throws an exception when the character does not exist in the font.
			if (c == '\n') {
				currentPosition.x = start.x; //startX
				currentPosition.y += m_Font->getSize();
				continue;
			}
			FontCharacter fch;
			if (m_Font->getCharacter(c, fch)) {
				//TODO make this 12 into something gotten from the font itself (or some shit, i dont know)
				drawSprite(fch.sprite, currentPosition + Vector2f((float)fch.left, (float)-fch.top + (float)m_Font->getSize() - 2.0f));

				currentPosition.x += (float) fch.xadvance;

				//Is this needed?
				currentPosition.y += (float) fch.yadvance;
			}
		}

	}

	void Graphics2D::drawSprite(const Sprite & sprite, const Vector2f & position)
	{
		if (drawing3D) {
			LOG_ERROR("Can't draw 2D when drawing in 3D");
		}
		setTexture(sprite.texture());

		batch.color(m_Color);

		batch.uv(sprite.uvs().topleft());
		batch.vertex(position + sprite.bounds().topleft());

		batch.uv(sprite.uvs().bottomleft());
		batch.vertex(position + sprite.bounds().bottomleft());

		batch.uv(sprite.uvs().bottomright());
		batch.vertex(position + sprite.bounds().bottomright());

		batch.uv(sprite.uvs().topright());
		batch.vertex(position + sprite.bounds().topright());
	}

	void Graphics2D::drawLine(const Vector2f & start, const Vector2f & end)
	{
		if (drawing3D) {
			LOG_ERROR("Can't draw 2D when drawing in 3D");
		}
		const float lw = m_LineWidth / 2.f;
		Vector2f dir = end - start;
		float length = dir.magnitude();
		dir /= length;
		Vector2f normal(dir.y, -dir.x);
		
		setTexture(m_WhiteTexture);
		batch.color(m_Color);
		batch.vertex(start + normal * lw);
		batch.vertex(start - normal * lw);
		batch.vertex(end - normal * lw);
		batch.vertex(end + normal * lw);
	}

	void Graphics2D::drawLine(const line2f & line)
	{
		drawLine(line.a, line.b);
	}

	void Graphics2D::drawPoint(const Vector2f & point)
	{
		if (m_PointType == PointType::CIRCLE) {
			drawCircle(point,m_PointSize / 2.0f, true);
		}
		else {
			drawRectangle(rectf(
				point.x - m_PointSize / 2.0f,
				point.y - m_PointSize / 2.0f,
				m_PointSize,
				m_PointSize
			), true);
		}
		
	}

	void Graphics2D::drawClear()
	{
		//TODO all the clipping and stuff?
		flush();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Graphics2D::setClip(const recti &rectangle)
	{
		flush();

		this->m_ClippingRectangle = rectangle;
		//Flush again to apply the clip
		flush();
	}

	void Graphics2D::resetClip()
	{
		flush();

		m_ClippingRectangle.x() = 0;
		m_ClippingRectangle.y() = 0;
		m_ClippingRectangle.width() = (int) Engine::getWindow().getWidth();
		m_ClippingRectangle.height() = (int) Engine::getWindow().getHeight();

		//Flush again to apply the clip
		flush();
	}

	void Graphics2D::setColor(const Color32 & color)
	{
		//TODO find out what is more efficient
		//Adding 4 bytes per vertex of memory to copy
		//Or add a drawcall

		this->m_Color = color;
	}

	//This should be removed. This cannot be happening (probably? )
	//There should be a custom Shader2D class, and maybe if this takes shared_ptr to Shader2D it can change it up
	void Graphics2D::setShader(std::shared_ptr<Shader> shader)
	{
		if (shader != m_Material->m_Shader) {
			flush();
			m_Material->m_Shader = shader;
		}
	}

	void Graphics2D::setDepth(float depth)
	{
		batch.depth(depth);
	}

	void Graphics2D::setTexture(std::shared_ptr<Texture> texture)
	{
		if (texture != m_Material->m_TextureMap) {
			flush();
			m_Material->m_TextureMap = texture;
		}
	}

	void Graphics2D::flush()
	{
		//Is Graphics2D responseable for this?
		Renderer::viewport(recti(0, 0, (int)Engine::getWindow().getWidth(), (int)Engine::getWindow().getHeight()));
		Renderer::clip(this->m_ClippingRectangle);

		if (batch.count() <= 0) {
			return;
		}

		calls++;

		//Disable lighting
		GraphicsState::m_Material = m_Material.get();
		GraphicsState::m_Skybox = nullptr;

		GraphicsState::matrixModel = Matrix4f::identity();
		GraphicsState::matrixView = Matrix4f::identity();
		GraphicsState::matrixProjection = Matrix4f::orthographic(0, Engine::getWindow().getWidth(), Engine::getWindow().getHeight(), 0, -100, 100);

		GraphicsState::prepare();

		batch.end();
		batch.begin(Primitive::QUADS);
	}
}
