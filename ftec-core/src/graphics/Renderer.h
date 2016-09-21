#pragma once

#include "VBORenderable.h"
#include "Material.h"
#include "Camera.h"
#include "math/vec3.h"
#include "Mesh.h"
#include "Light.h"

namespace ftec {
	class Renderer {

	public:
		Renderer() = delete;

		//Use Graphics::draw instead
		static void drawDirect(const VBORenderable &renderable, const Material &material, const Camera &camera, const mat4 &modelMatrix = mat4::identity());
		static void drawDirect(const Mesh &mesh, const Material &material, const Light &light, const Camera &camera, const mat4 &modelMatrix = mat4::identity());
		static void drawDirect(const Mesh &mesh, const Material &material, const Light &light, const mat4 &projectionMatrix = mat4::identity(), const mat4 &viewMatrix = mat4::identity(), const mat4 &modelMatrix = mat4::identity());

		//Sets the clipping plane
		static void clip(int x, int y, int width, int height);
		//Sets the viewport
		static void viewport(int x, int y, int width, int height);

		//Sets both the viewport and the clipping plane
		static void renderport(int x, int y, int width, int height);
	};
}