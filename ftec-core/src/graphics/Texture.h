#pragma once

#include "resources/ResourceManager.h"

namespace ftec {
	class Texture : public ManagableResource {
	public:
		Texture();
		~Texture();

		static std::shared_ptr<Texture> load(const std::string &name)
		{
			return std::make_shared<Texture>();
		}
	};
}