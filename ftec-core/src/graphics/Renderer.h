#pragma once

#include "VBORenderable.h"
#include "Material.h"
#include "Camera.h"
#include "math/vec3.h"
#include "math/rect.h"
#include "Mesh.h"
#include "Light.h"

namespace ftec {
	class Renderer {

	public:
		Renderer() = delete;

		//Use Graphics::draw instead
		static void drawDirect(const Mesh &mesh, const Material &material, const Light &light, const Camera &camera, const mat4 &modelMatrix = mat4::identity());
		static void drawDirect(const Mesh &mesh, const Material &material, const Light &light, const mat4 &projectionMatrix = mat4::identity(), const mat4 &viewMatrix = mat4::identity(), const mat4 &modelMatrix = mat4::identity());
		static void drawDirect(const Mesh &mesh, const Material &material, const mat4 &modelMatrix = mat4::identity());

		//Sets the clipping plane
		static void clip(const rect2i &rectangle);
		//Sets the viewport
		static void viewport(const rect2i &rectangle);

		//Sets both the viewport and the clipping plane
		static void renderport(const rect2i &rectangle);
	};
}