#pragma once

#include "resources/ResourceManager.h"
#include "GL.h"
#define DEFAULT_TEXTURE_CHECKERBOARD "CHECKERBOARD"
#define DEFAULT_TEXTURE_WHITE "WHITE"

namespace ftec {
	class Texture : public ManagableResource {
	private:
		GLuint m_TextureID;
	public:
		Texture();
		~Texture();

		void bind() const;
		void unbind() const;

		static std::shared_ptr<Texture> load(const std::string &name);
	};
}