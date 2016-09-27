#pragma once

#include "resources/ResourceManager.h"

namespace ftec {
	class Font : public ManagableResource {



		std::shared_ptr<Font> load(const std::string &name);
	};
}