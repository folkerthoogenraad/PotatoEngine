#include "Cubemap.h"

#include "GL.h"
#include "logger/log.h"
#include "ImageHelper.h"
#include <vector>

namespace ftec {

	Cubemap::Cubemap()
	{
		glGenTextures(1, &m_TextureID);

		bind();

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		unbind();
	}

	Cubemap::~Cubemap()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Cubemap::bind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
	}
	void Cubemap::unbind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	std::shared_ptr<Cubemap> Cubemap::load(const std::string & name)
	{
		std::vector<std::string> faces;

		faces.push_back(name + "_rt.jpg");
		faces.push_back(name + "_lf.jpg");
		faces.push_back(name + "_dn.jpg");//Flipped up and down (TODO fixme)
		faces.push_back(name + "_up.jpg");
		faces.push_back(name + "_bk.jpg");
		faces.push_back(name + "_ft.jpg");

		auto cubemap = std::make_shared<Cubemap>();
		cubemap->bind();

		for (int i = 0; i < faces.size(); i++)
		{
			//Load the actual image
			vec2i size = glLoadImage(faces[i], GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
			if (size.x < 0) {
				TERMINATE("Failed to load texture: " << name);
			}
		}
		cubemap->unbind();

		return cubemap;
	}
}
