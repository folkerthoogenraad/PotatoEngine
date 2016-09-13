#include "Texture.h"
#include "logger/log.h"
#define FREEIMAGE_LIB
#include <FreeImage.h>

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
			//Load the image using FreeImage

			auto loadImage = [&](GLuint texID) {

				//image format
				FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
				//pointer to the image, once loaded
				FIBITMAP *dib(0);
				//pointer to the image data
				BYTE* bits(0);
				//image width and height
				unsigned int width(0), height(0);

				//check the file signature and deduce its format
				fif = FreeImage_GetFileType(name.c_str(), 0);
				//if still unknown, try to guess the file format from the file extension
				if (fif == FIF_UNKNOWN)
					fif = FreeImage_GetFIFFromFilename(name.c_str());
				//if still unkown, return failure
				if (fif == FIF_UNKNOWN)
					return false;

				//check that the plugin has reading capabilities and load the file
				if (FreeImage_FIFSupportsReading(fif))
					dib = FreeImage_Load(fif, name.c_str());

				//if the image failed to load, return failure
				if (!dib)
					return false;

				FIBITMAP *image = FreeImage_ConvertTo32Bits(dib);

				//retrieve the image data
				bits = FreeImage_GetBits(image);
				//get the image width and height
				width = FreeImage_GetWidth(image);
				height = FreeImage_GetHeight(image);
				//if this somehow one of these failed (they shouldn't), return failure
				if ((bits == 0) || (width == 0) || (height == 0))
					return false;

				//bind to the new texture ID
				glBindTexture(GL_TEXTURE_2D, texID);
				//store the texture data for OpenGL use
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
					0, GL_BGRA, GL_UNSIGNED_BYTE, bits);

				//Free FreeImage's copy of the data
				FreeImage_Unload(dib);
				FreeImage_Unload(image);

				//return success
				return true;
			};

			if (!loadImage(texture->m_TextureID)) {
				TERMINATE("Failed to load texture...");
			}

		}

		//TODO load stuff and shit
		return texture;
	}
}
