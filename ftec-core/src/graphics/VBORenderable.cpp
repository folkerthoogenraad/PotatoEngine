#include "VBORenderable.h"

namespace ftec {
	VBORenderable::VBORenderable(size_t size)
		: m_Vertices(), firstIndex(0), lastIndex(size)
	{
		m_Vertices.resize(size);

		glGenBuffers(1, &m_Vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(VBORVertex), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	VBORenderable::~VBORenderable()
	{
		glDeleteBuffers(1, &m_Vbo);
	}

	void VBORenderable::update(size_t offset, size_t amount)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(VBORVertex), amount * sizeof(VBORVertex), &m_Vertices[offset]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}