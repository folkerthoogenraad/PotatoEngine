#pragma once
#include "resources/ResourceManager.h"

typedef unsigned int GLuint;

namespace ftec {
	class Cubemap : public ManagableResource {
		GLuint m_TextureID;
	public:
		Cubemap();
		~Cubemap();

		void bind() const;
		void unbind() const;

		static std::shared_ptr<Cubemap> load(const std::string &name);
	};
}