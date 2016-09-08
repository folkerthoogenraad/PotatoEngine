#pragma once

#include <gl/glew.h>
#include "math/vec3.h"
#include <vector>

namespace ftec {
	class VBORenderable {
		struct VBORVertex {
			vec3 position;
		};

	public:
		std::vector<VBORVertex> m_Vertices;
	private:
		GLuint m_Vbo;
	public:
		VBORenderable(size_t size);
		~VBORenderable();

		///Offset and amount in vertices
		void update(size_t offset, size_t amount);
	};
}