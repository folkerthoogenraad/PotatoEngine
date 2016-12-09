#include "Renderer2D.h"

#include "Drawable2D.h"
#include "math/mat3.h"

#include <assert.h>

namespace ftec {
	
	Renderer2D::Renderer2D()
	{
		//Push the first matrix on the matrix stack, so there always is one
		m_TransformationStack.push_back(mat3f());
	}
	Renderer2D::~Renderer2D()
	{

	}

	void Renderer2D::draw(Drawable2D & drawable)
	{
		drawable.draw(*this);
	}

	const mat3f &Renderer2D::getTransformationMatrix() const
	{
		return m_TransformationStack.back();
	}

	void Renderer2D::flush()
	{
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
		if(m_Renderer.batch.primitive() != primitive)
			m_Renderer.flush();
	}

	Paint::~Paint()
	{
	}
	void Paint::vertex(float x, float y)
	{
	}
	void Paint::depth(float z)
	{
		m_Depth = z;
	}
	void Paint::color(const color32 & color)
	{
	}
	void Paint::uv(float u, float v)
	{
	}
}
