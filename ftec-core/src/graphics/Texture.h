#pragma once

#include "resources/ManageableResource.h"
#include <memory>
#include <string>

#define DEFAULT_TEXTURE_CHECKERBOARD "CHECKERBOARD"
#define DEFAULT_TEXTURE_WHITE "WHITE"
#define DEFAULT_TEXTURE_NORMAL "NORMAL"
#define DEFAULT_TEXTURE_BLACK "BLACK"
#define DEFAULT_TEXTURE_GRAY "GRAY"
#define DEFAULT_TEXTURE_DARK_GRAY "DARK_GRAY"


namespace ftec {
	class Texture : public ManagableResource {

	public:
		enum InterpolationMode {
			LINEAR, NEAREST, LINEAR_MIPMAP
		};

	private:
		unsigned int m_TextureID;
		int m_Width, m_Height;
	public:
		Texture();
		~Texture();

		void bind() const;
		void unbind() const;

		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }

		void setMagnifyScaling(InterpolationMode scaling);
		void setMinifyScaling(InterpolationMode scaling);

		void setScaling(InterpolationMode min, InterpolationMode mag);

		inline unsigned int id() const { return m_TextureID; }

		static std::shared_ptr<Texture> load(const std::string &name);

		friend class Font; //Why is this here again?
	};
}