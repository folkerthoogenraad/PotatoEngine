#pragma once

#include "GL.h"
#include "math/vec3.h"
#include "math/vec2.h"
#include <vector>

//TODO make this non copyable for resource reasons
//Pretty deprecated

namespace ftec {
	class VBORenderable {
	public:
		struct VBORVertex {
			vec3f position;
			vec3f normal;
			vec2f uv;
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

		///Realocates m_Vertices.size() on the OpenGL side of things
		void realocate();
	};
}