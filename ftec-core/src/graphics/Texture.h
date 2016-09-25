#pragma once

#include "resources/ResourceManager.h"
#include "GL.h"
#define DEFAULT_TEXTURE_CHECKERBOARD "CHECKERBOARD"
#define DEFAULT_TEXTURE_WHITE "WHITE"

namespace ftec {
	class Texture : public ManagableResource {
	private:
		GLuint m_TextureID;
		int m_Width, m_Height;
	public:
		Texture();
		~Texture();

		void bind() const;
		void unbind() const;

		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }

		inline GLuint id() const { return m_TextureID; }

		static std::shared_ptr<Texture> load(const std::string &name);
	};
}