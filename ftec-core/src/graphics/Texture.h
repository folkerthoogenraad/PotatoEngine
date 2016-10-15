#pragma once

#include "resources/ResourceManager.h"
#include "GL.h"

#define DEFAULT_TEXTURE_CHECKERBOARD "CHECKERBOARD"
#define DEFAULT_TEXTURE_WHITE "WHITE"
#define DEFAULT_TEXTURE_NORMAL "NORMAL"
#define DEFAULT_TEXTURE_BLACK "BLACK"

#define INTERPOLATION_LINEAR GL_LINEAR
#define INTERPOLATION_NEAREST GL_NEAREST
#define INTERPOLATION_LINEAR_MIPMAP GL_LINEAR_MIPMAP_LINEAR

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

		void setMagnifyScaling(int scaling);
		void setMinifyScaling(int scaling);

		void setScaling(int min, int mag);

		inline GLuint id() const { return m_TextureID; }

		static std::shared_ptr<Texture> load(const std::string &name);
	};
}