#pragma once
#include <memory>
#include "Shader.h"
#include "Texture.h"

namespace ftec {
	struct Material {
		std::shared_ptr<Texture> texture;
		std::shared_ptr<Shader> shader;
	};
}