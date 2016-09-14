#pragma once

#include "Texture.h"
#include "GL.h"

namespace ftec {
	class RenderBuffer {
	private: //might someday be public?
		GLuint m_Framebuffer;
		Texture m_DepthAttachment;
		Texture m_ColorAttachment;
		int m_Width;
		int m_Height;
	public:
		RenderBuffer(int width, int height);
		~RenderBuffer();

		void bind() const;
		void unbind() const;

		const Texture &getTexture() const { return m_ColorAttachment; }
		const Texture &getDepthTexture() const { return m_DepthAttachment; }
	};
}