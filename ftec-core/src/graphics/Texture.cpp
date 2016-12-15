#include "Texture.h"

#include "logger/log.h"
#include "ImageHelper.h"
#include "GL.h"

#define INTERPOLATION_LINEAR GL_LINEAR
#define INTERPOLATION_NEAREST GL_NEAREST
#define INTERPOLATION_LINEAR_MIPMAP GL_LINEAR_MIPMAP_LINEAR

namespace ftec {

	static int getGLInterpolationMode(Texture::InterpolationMode m)
	{
		switch (m) {
		case Texture::LINEAR:
			return GL_LINEAR;
		case Texture::NEAREST:
			return GL_NEAREST;
		case Texture::LINEAR_MIPMAP:
			return GL_LINEAR_MIPMAP_LINEAR;
		default:
			LOG_ERROR("Unkown interpolation mode " << m);
			return GL_NEAREST;
		}
	}

	Texture::Texture()
		:m_TextureID(0)
	{
		glGenTextures(1, &m_TextureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

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

	void Texture::setMagnifyScaling(InterpolationMode scaling)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getGLInterpolationMode(scaling));
		unbind();
	}

	void Texture::setMinifyScaling(InterpolationMode scaling)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getGLInterpolationMode(scaling));
		unbind();
	}

	void Texture::setScaling(InterpolationMode min, InterpolationMode mag)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getGLInterpolationMode(min));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getGLInterpolationMode(mag));
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
			texture->m_Width = 2;
			texture->m_Height = 2;
			texture->unbind();
		}
		else if (name == DEFAULT_TEXTURE_WHITE) {
			float data[] = {
				1,1,1
			};
			texture->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_FLOAT, data);
			texture->m_Width = 1;
			texture->m_Height = 1;
			texture->unbind();
		}

		else if (name == DEFAULT_TEXTURE_BLACK) {
			float data[] = {
				0,0,0
			};
			texture->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_FLOAT, data);
			texture->m_Width = 1;
			texture->m_Height = 1;
			texture->unbind();
		}

		else if (name == DEFAULT_TEXTURE_GRAY) {
			float data[] = {
				0.5f,0.5f,0.5f
			};
			texture->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_FLOAT, data);
			texture->m_Width = 1;
			texture->m_Height = 1;
			texture->unbind();
		}
		else if (name == DEFAULT_TEXTURE_DARK_GRAY) {
			float data[] = {
				0.1f,0.1f,0.1f
			};
			texture->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_FLOAT, data);
			texture->m_Width = 1;
			texture->m_Height = 1;
			texture->unbind();
		}

		else if (name == DEFAULT_TEXTURE_NORMAL) {
			float data[] = {
				0.5f,0.5f,1.0f
			};
			texture->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_FLOAT, data);
			texture->m_Width = 1;
			texture->m_Height = 1;
			texture->unbind();
		}
		else {
			//Load the image using FreeImage

			texture->bind();

			Vector2i size = glLoadImage(name, GL_TEXTURE_2D);

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
