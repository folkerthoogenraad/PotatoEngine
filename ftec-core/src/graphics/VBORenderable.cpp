#include "VBORenderable.h"
#include "GL.h"

namespace ftec {
	VBORenderable::VBORenderable(unsigned int size)
		: m_Vertices(), firstIndex(0), lastIndex(size)
	{
		m_Vertices.resize(size);

		glGenBuffers(1, &m_Vbo);
		realocate();
	}
	VBORenderable::~VBORenderable()
	{
		glDeleteBuffers(1, &m_Vbo);
	}

	void VBORenderable::update(unsigned int offset, unsigned int amount)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(VBORVertex), amount * sizeof(VBORVertex), &m_Vertices[offset]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VBORenderable::realocate()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(VBORVertex), &m_Vertices[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}