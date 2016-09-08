#pragma once

#include <gl/glew.h>
#include "math/vec3.h"

namespace ftec {
	class VBORenderable {
		struct VBORVertex {
			vec3 position;
		};
	private:
		GLuint m_Vbo;
	public:
		void update();
	};
}