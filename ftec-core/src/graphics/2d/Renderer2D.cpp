#include "Renderer2D.h"

#include "Drawable2D.h"

#include "math/Matrix3.h"
#include "math/Matrix4.h"

#include "graphics/Shader.h"
#include "graphics/Texture.h"

#include "logger/log.h"

#include "engine/Engine.h"
#include "resources/ResourceManager.h"

#include "graphics/Renderer.h"
#include "graphics/Window.h"


#define VERTEX_SHADER_SOURCE "#version 150\n\nuniform mat4 u_MatrixModel;\nuniform mat4 u_MatrixView;\nuniform mat4 u_MatrixProjection;\n\nin vec3 position;\nin vec2 uv;\nin vec4 color;\n\nout vec2 v_Uv;\nout vec4 v_Color;\n\nvoid main()\n{\n\tv_Uv = uv;\n\tv_Color = color;\n\n\tgl_Position = u_MatrixProjection * u_MatrixView * u_MatrixModel * vec4(position, 1.0);\n}"
#define FRAGMENT_SHADER_SOURCE "#version 150\n\nuniform sampler2D u_Texture;\n\nin vec2 v_Uv;\nin vec4 v_Color;\n\nout vec4 FragColor;\n\nvoid main()\n{\n\tFragColor = texture(u_Texture, v_Uv) * v_Color;\n}"

#include <assert.h>

namespace ftec {
	
	Renderer2D::Renderer2D()
	{
		//Push the first matrix on the matrix stack, so there always is one
		m_TransformationStack.push_back(Matrix3f());

		m_WhiteTexture = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);

		m_Shader = std::make_shared<Shader>(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
		
		m_CurrentTexture = m_WhiteTexture;

		//TODO TODO TODO
		m_Shader->use();

		m_ModelLocation = m_Shader->getUniformLocation("u_MatrixModel");
		m_ViewLocation = m_Shader->getUniformLocation("u_MatrixView");
		m_ProjectionLocation = m_Shader->getUniformLocation("u_MatrixProjection");

		m_Shader->setUniform(m_ViewLocation, Matrix4f::identity());
		m_Shader->setUniform(m_ProjectionLocation, Matrix4f::identity());

		glActiveTexture(GL_TEXTURE0);
		int textureLocation = m_Shader->getUniformLocation("u_Texture");
		m_Shader->setUniform(textureLocation, 0);

		auto i = recti(0, 0, (int)Engine::getWindow().getWidth(), (int)Engine::getWindow().getHeight());
		Renderer::viewport(i);
		Renderer::clip(i);

	}

	Renderer2D::~Renderer2D()
	{
		if (batch.isDrawing())
			batch.end();
	}

	void Renderer2D::draw(Drawable2D & drawable)
	{
		drawable.draw(*this);
	}

	const Matrix3f &Renderer2D::getTransformationMatrix() const
	{
		return m_TransformationStack.back();
	}

	void Renderer2D::flush()
	{
		m_CurrentTexture->bind();

		m_Shader->setUniform(m_ModelLocation, this->getTransformationMatrix().expand());

		batch.flush();
	}

	void Transformation::change()
	{
		//Can't change the transformation in any way if this is not true
		assert(m_MatrixIndex == m_Renderer.m_TransformationStack.size() - 1);

		//Flush the renderer, because something is about to change.
		//The flush itself will figure out whether or not it is needed to flush.
		//No need to do redundant stuff
		m_Renderer.flush();
	}

	Transformation::Transformation(Renderer2D & r)
		:m_Renderer(r)
	{
		//Duplicate back and place it at the back
		m_Renderer.flush();

		m_MatrixIndex = r.m_TransformationStack.size();
		
		m_Renderer.m_TransformationStack.push_back(
			m_Renderer.m_TransformationStack.back()
		);
	}

	Transformation::~Transformation()
	{
		change();
		m_Renderer.m_TransformationStack.pop_back();
	}

	void Transformation::translate(float x, float y)
	{
		change();
		m_Renderer.m_TransformationStack.back().translate(x, y);
	}

	void Transformation::scale(float x, float y)
	{
		change();
		m_Renderer.m_TransformationStack.back().scale(x, y);
	}

	void Transformation::rotate(float angle)
	{
		change();
		m_Renderer.m_TransformationStack.back().rotate(angle);
	}

	Paint::Paint(Renderer2D & r, Primitive primitive)
		: m_Renderer(r), m_Primitive(primitive)
	{
		if(m_Renderer.batch.isDrawing() && m_Renderer.batch.primitive() != primitive)
			m_Renderer.flush();

		if (!m_Renderer.batch.isDrawing())
			m_Renderer.batch.begin(primitive);
	}

	Paint::~Paint()
	{

	}
	void Paint::vertex(float x, float y)
	{
		m_Renderer.batch.vertex(Vector3f(x, y, m_Depth));
	}
	void Paint::depth(float z)
	{
		m_Depth = z;
	}
	void Paint::color(Color32 color)
	{
		m_Renderer.batch.color(std::move(color));
	}
	void Paint::uv(float u, float v)
	{
		m_Renderer.batch.uv(Vector2f(u,v));
	}
}
