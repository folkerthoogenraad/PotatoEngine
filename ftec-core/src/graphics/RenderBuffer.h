#pragma once

#include "Texture.h"
#include "GL.h"

namespace ftec {
	//Currently this class does not work, and should be reworked
	class RenderBuffer {
	private:
		GLuint m_Framebuffer;
		std::shared_ptr<Texture> m_DepthAttachment;
		std::shared_ptr<Texture> m_ColorAttachment;
		int m_Width;
		int m_Height;
	public:
		RenderBuffer(int width, int height);
		~RenderBuffer();

		void bind() const;
		void unbind() const;

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

		std::shared_ptr<Texture>  getTexture() const { return m_ColorAttachment; }
		std::shared_ptr<Texture> getDepthTexture() const { return m_DepthAttachment; }
	};
}