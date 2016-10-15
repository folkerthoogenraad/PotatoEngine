#include "Texture.h"
#include "logger/log.h"
#include "ImageHelper.h"

namespace ftec {
	Texture::Texture()
		:m_TextureID(0)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::setMagnifyScaling(int scaling)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, scaling);
		unbind();
	}

	void Texture::setMinifyScaling(int scaling)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, scaling);
		unbind();
	}

	void Texture::setScaling(int min, int mag)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
		unbind();
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

		else if (name == DEFAULT_TEXTURE_BLACK) {
			float data[] = {
				0,0,0
			};
			texture->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_FLOAT, data);
			texture->unbind();
		}

		else if (name == DEFAULT_TEXTURE_NORMAL) {
			float data[] = {
				0.5f,0.5f,1.0f
			};
			texture->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_FLOAT, data);
			texture->unbind();
		}
		else {
			//Load the image using FreeImage

			texture->bind();

			vec2i size = glLoadImage(name, GL_TEXTURE_2D);

			if (size.x < 0) {
				TERMINATE("Failed to load texture: " << name);
			}

			texture->m_Width = size.x;
			texture->m_Height = size.y;

			glGenerateMipmap(GL_TEXTURE_2D);

			texture->unbind();
		}

		//TODO load stuff and shit
		return texture;
	}
}
