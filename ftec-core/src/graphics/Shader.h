#pragma once

#include "resources/ResourceManager.h"

namespace ftec {
	class Shader : public ManagableResource {
	public:
		Shader() = default;
		~Shader() = default;

		static std::shared_ptr<Shader> load(const std::string &name);
	};
}