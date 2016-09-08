#pragma once

#include "VBORenderable.h"
#include "Material.h"
#include "math/vec3.h"

namespace ftec {
	class Renderer {

	public:
		Renderer() = default;
		~Renderer() = default;

		//Todo add other options ofcourse
		void draw(const VBORenderable &renderable, const Material &material, const vec3 &position);

	};
}