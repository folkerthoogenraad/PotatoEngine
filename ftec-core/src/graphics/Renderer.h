#pragma once

#include "VBORenderable.h"
#include "Material.h"
#include "Camera.h"
#include "math/vec3.h"
#include "Mesh.h"

namespace ftec {
	class Renderer {

	public:
		Renderer() = delete;

		//Use Graphics::draw instead
		static void drawDirect(const VBORenderable &renderable, const Material &material, const Camera &camera, const mat4 &modelMatrix = mat4::identity());
		static void drawDirect(const Mesh &mesh, const Material &material, const Camera &camera, const mat4 &modelMatrix = mat4::identity());

	};
}