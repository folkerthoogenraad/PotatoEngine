#include "RenderBuffer.h"

namespace ftec {

	RenderBuffer::RenderBuffer(int width, int height)
		: m_Width(width), m_Height(height)
	{
		glGenFramebuffers(1, &m_Framebuffer);
	}

	RenderBuffer::~RenderBuffer()
	{
		glDeleteFramebuffers(1, &m_Framebuffer);
	}

	void RenderBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
	}

	void RenderBuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}