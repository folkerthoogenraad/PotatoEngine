#pragma once

#include <gl/glew.h>
#include "math/vec3.h"
#include "math/vec2.h"
#include <vector>

//TODO make this non copyable for resource reasons

namespace ftec {
	class VBORenderable {
	public:
		struct VBORVertex {
			vec3 position;
			vec3 normal;
			vec2 uv;
		};

	public:
		std::vector<VBORVertex> m_Vertices;
		unsigned int firstIndex;
		unsigned int lastIndex;
		GLuint m_Vbo;
	public:
		VBORenderable(size_t size);
		~VBORenderable();

		///Offset and amount in vertices
		void update(size_t offset, size_t amount);
	};
}