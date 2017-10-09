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

#include <array>
#include <assert.h>

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

		batch.setRequestFlush(std::bind(&Graphics2D::flush, this));
		batch.texureIndex(1);
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

	void Graphics2D::drawBezier(const curves::VCubicBezier & bezier)
	{
		Vector2f from = bezier.p0;

		const int subdivisions = 30;
		const float subd = (float)subdivisions;
		
		for (int i = 1; i <= subdivisions; i++) {
			Vector2f to = bezier.interpolate(i / subd);
			drawLine(from, to);
			from = to;
		}
	}

	void Graphics2D::drawAutoBezier(const Vector2f & from, const Vector2f & to)
	{
		curves::VCubicBezier bezier;

		bezier.p0 = from;

		bezier.p1 = Vector2f((from.x + to.x) / 2.0f, from.y);
		bezier.p2 = Vector2f((from.x + to.x) / 2.0f, to.y);

		bezier.p3 = to;

		drawBezier(bezier);
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

	void Graphics2D::drawSprite(const Sprite & sprite, Vector2f position)
	{
		drawSprite(sprite, position, Vector2f(1, 1), 0);
	}

	void Graphics2D::drawSprite(const Sprite & sprite, Rectanglef rectangle)
	{
		drawSprite(sprite, rectangle.position, rectangle.size / sprite.size(), 0);
	}

	void Graphics2D::drawSprite(const Sprite & sprite, Vector2f position, Vector2f scale, float rotation)
	{
		if (drawing3D) {
			LOG_ERROR("Can't draw 2D when drawing in 3D");
		}

		Vector2f right = Vector2f(1, 0);
		Vector2f down = Vector2f(0, 1);

		Vector2f size = sprite.size() * scale;

		if (rotation != 0) {
			float s = sin(rotation);
			float c = cos(rotation);

			right = Vector2f(c, -s);
			down = Vector2f(s, c);
		}

		position -= sprite.offset().x * scale.x * right + sprite.offset().y * scale.y * down;


		setTexture(sprite.texture());
		batch.color(m_Color);

		if (sprite.getType() == Sprite::Default) {
			batch.uv(sprite.uvs().topleft());
			batch.vertex(position);

			batch.uv(sprite.uvs().bottomleft());
			batch.vertex(position + down * size.y);

			batch.uv(sprite.uvs().bottomright());
			batch.vertex(position + down * size.y + right * size.x);

			batch.uv(sprite.uvs().topright());
			batch.vertex(position + right * size.x);
		}
		if (sprite.getType() == Sprite::Sliced) {
			float width = sprite.size().width;
			float height= sprite.size().height;
			
			SpriteSlices slices = sprite.getSlices();
			Rectanglef uvs = sprite.uvs();

			Vector2f uvOffset = uvs.topleft();
			Vector2f uvRight(1, 0);
			Vector2f uvDown(0, 1);
			
			std::array<float, 4> widthf{
				0,
				(slices.left / width),
				1 - (slices.right / width),
				1,
			};

			std::array<float, 4> heightf{
				0,
				(slices.top / height),
				1 - (slices.bottom / height),
				1,
			};


			std::array<float, 4> widthp{
				0,
				(slices.left / size.x),
				1 - (slices.right / size.x),
				1,
			};

			std::array<float, 4> heightp{
				0,
				(slices.top / size.y),
				1 - (slices.bottom / size.y),
				1,
			};

			auto addVertex = [&](int i, int j) {
				batch.uv(uvOffset
					+ uvRight * widthf[i] * uvs.size.x
					+ uvDown * heightf[j] * uvs.size.y);
				batch.vertex(position
					+ right * widthp[i] * size.x
					+ down * heightp[j] * size.y);
			};

			for (int i = 0; i < widthf.size() - 1; i++) {
				for (int j = 0; j < heightf.size() - 1; j++) {
					addVertex(i, j);
					addVertex(i, j + 1);
					addVertex(i + 1, j + 1);
					addVertex(i + 1, j);
				}
			}
		}

	}

#if 0
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
#endif

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
		if (texture != m_Material->m_TextureMaps[m_CurrentTextureIndex]) {

			size_t max = m_Material->m_TextureMaps.size();

			// Search for the texture in the current materials
			for (int i = 0; i < max; i++) {
				if (m_Material->m_TextureMaps[i] == texture) {
					m_CurrentTextureIndex = i;
					batch.texureIndex(m_CurrentTextureIndex); // Oh shit, this is double
					return;
				}
			}

			m_CurrentTextureIndex++;

			if (m_CurrentTextureIndex >= max) {
				flush();
				m_CurrentTextureIndex = 0;
			}

			
			batch.texureIndex(m_CurrentTextureIndex); // Oh shit, this is double
			
			m_Material->m_TextureMaps[m_CurrentTextureIndex] = texture;
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

		for (size_t i = 0; i < m_Material->m_TextureMaps.size(); i++)
			m_Material->m_TextureMaps[i].reset();

		m_CurrentTextureIndex = 0;
	}
}
