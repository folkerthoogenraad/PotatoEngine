#include "RenderBuffer.h"
#include "logger/log.h"

namespace ftec {

	RenderBuffer::RenderBuffer(int width, int height)
		: m_Width(width), m_Height(height)
	{
		m_ColorAttachment = std::make_shared<Texture>();
		m_DepthAttachment = std::make_shared<Texture>();

		glGenFramebuffers(1, &m_Framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

		m_ColorAttachment->bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		m_DepthAttachment->bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment->id(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment->id(), 0);
	
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) {
			LOG_ERROR("Failed to create frame buffer extention");
		}
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