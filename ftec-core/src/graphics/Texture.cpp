#include "Texture.h"

namespace ftec {
	Texture::Texture()
		:m_TextureID(0)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	std::shared_ptr<Texture> Texture::load(const std::string &name)
	{
		auto texture = std::make_shared<Texture>();
		if (name == DEFAULT_TEXTURE_CHECKERBOARD) {
			float data[] = {
				0,0,0, 1,1,1,
				1,1,1, 0,0,0
			};
			texture->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGB, GL_FLOAT, data);
			texture->unbind();
		}
		else if (name == DEFAULT_TEXTURE_WHITE) {
			float data[] = {
				1,1,1
			};
			texture->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_FLOAT, data);
			texture->unbind();
		}
		else {

		}

		//TODO load stuff and shit
		return texture;
	}
}
