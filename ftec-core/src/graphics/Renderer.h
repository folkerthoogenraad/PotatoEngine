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

		static void drawDirect(const Mesh &mesh);

		//Sets the clipping plane
		static void clip(const rect2i &rectangle);
		//Sets the viewport
		static void viewport(const rect2i &rectangle);

		//Sets both the viewport and the clipping plane
		static void renderport(const rect2i &rectangle);

		static void clear();
	};
}