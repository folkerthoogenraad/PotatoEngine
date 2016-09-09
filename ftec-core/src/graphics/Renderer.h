#pragma once

#include "VBORenderable.h"
#include "Material.h"
#include "Camera.h"
#include "math/vec3.h"

namespace ftec {
	class Renderer {

	public:
		Renderer() = delete;

		//Todo add other options ofcourse
		static void draw(const VBORenderable &renderable, const Material &material, const Camera &camera, const mat4 &modelMatrix = mat4::identity());

	};
}