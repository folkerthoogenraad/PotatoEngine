#pragma once

#include <memory>							//For std::shared_ptr
#include <string>							//For std::string

#include "resources/ManageableResource.h"	//For ManageableResource

namespace ftec {
	class Cubemap : public ManagableResource {
		uint32_t m_TextureID;
	public:
		Cubemap();
		~Cubemap();

		void bind() const;
		void unbind() const;

		static std::shared_ptr<Cubemap> load(const std::string &name);
	};
}