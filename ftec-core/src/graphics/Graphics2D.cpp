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

#include "math/Rectangle.h"

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

		m_Material = std::make_shared<Material2D>(Engine::getResourceManager().load<Shader>("shaders/default2d"));

		m_Material->m_TextureMaps[0] = m_WhiteTexture;

		m_Color = Color32(255, 255, 255, 255);
	}

	Graphics2D::~Graphics2D()
	{
		if (batch.isDrawing()) {
			end();
		}
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

	void Graphics2D::begin3D(Rectanglei rectangle)
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

	void Graphics2D::drawRectangle(const Rectanglef & rectangle, bool fill)
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

	void Graphics2D::drawCircle(const Vector2f & center, float radius, bool fill)
	{
		if (drawing3D) {
			LOG_ERROR("Can't draw 2D when drawing in 3D");
		}

		drawArc(center, radius, fill, 0, PI * 2);
	}

	void Graphics2D::drawCircle(const Circlef & circle, bool fill)
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
		//TODO TODO TODO
		//Fix this when working with low graphics memory situations.
		//This uses more than one shader though, now it can use just the same shader
		//LOG("WONT WORK CURRENTLY. NEEDS DIFFERENT SHADER WITH texture().r as color component!");

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

	void Graphics2D::drawSprite(const Sprite & sprite, const Vector3f & position)
	{
		float d = batch.depth();

		batch.depth(position.z);

		drawSprite(sprite, Vector2f(position.x, position.y));

		setDepth(d);
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

	void Graphics2D::drawSprite(const Sprite & sprite, const Matrix3f & transformation)
	{

		if (drawing3D) {
			LOG_ERROR("Can't draw 2D when drawing in 3D");
		}
		setTexture(sprite.texture());

		Vector3f positions[4] = {
			Vector3f(sprite.bounds().topleft()),
			Vector3f(sprite.bounds().bottomleft()),
			Vector3f(sprite.bounds().bottomright()),
			Vector3f(sprite.bounds().topright())
		};

		for (int i = 0; i < 4; i++)
			positions[i].z = 1;

		batch.color(m_Color);

		batch.uv(sprite.uvs().topleft());
		batch.vertex(transformation * positions[0]);

		batch.uv(sprite.uvs().bottomleft());
		batch.vertex(transformation * positions[1]);

		batch.uv(sprite.uvs().bottomright());
		batch.vertex(transformation * positions[2]);

		batch.uv(sprite.uvs().topright());
		batch.vertex(transformation * positions[3]);
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

	void Graphics2D::drawLine(const Line2f & line)
	{
		drawLine(line.a, line.b);
	}

	void Graphics2D::drawPoint(const Vector2f & point)
	{
		if (m_PointType == PointType::CIRCLE) {
			drawCircle(point,m_PointSize / 2.0f, true);
		}
		else {
			drawRectangle(Rectanglef(
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

	void Graphics2D::setColor(const Color32 & color)
	{
		//TODO find out what is more efficient
		//Adding 4 bytes per vertex of memory to copy
		//Or add a drawcall

		this->m_Color = color;
	}

	void Graphics2D::setDepth(float depth)
	{
		batch.depth(depth);
	}

	void Graphics2D::setCamera(Camera camera)
	{
		flush();
		this->m_Camera = std::move(camera);
	}

	void Graphics2D::setTexture(std::shared_ptr<Texture> texture)
	{
		if (texture != m_Material->m_TextureMaps[0]) {
			flush();
			m_Material->m_TextureMaps[0] = texture;
		}
	}

	void Graphics2D::flush()
	{
		if (batch.count() <= 0) {
			return;
		}

		//Just for debugging actually
		calls++;

		float bufferWidth = Engine::getWindow().getWidth();
		float bufferHeight = Engine::getWindow().getHeight();

		//TODO Is Graphics2D responseable for this?
		Rectanglei clipping(0, 0, (int)bufferWidth, (int)bufferHeight);
		Rectanglei viewport(
			(int)(m_Camera.m_Viewport.x() * bufferWidth), 
			(int)(m_Camera.m_Viewport.y() * bufferHeight),
			(int)(m_Camera.m_Viewport.width() * bufferWidth),
			(int)(m_Camera.m_Viewport.height() * bufferHeight)
		);

		Renderer::clip(clipping);
		Renderer::viewport(viewport);

		GraphicsState::m_Material = m_Material.get();
		GraphicsState::matrixModel = Matrix4f::identity();
		GraphicsState::matrixView = m_Camera.getViewMatrix();
		GraphicsState::matrixProjection = m_Camera.getProjectionMatrix();

		//TODO optimize this obviously
		GraphicsState::prepare();

		batch.flush();
	}
}
