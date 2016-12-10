#pragma once

#include <vector>

#include "math/Vector3.h"
#include "math/Vector2.h"

//TODO make this non copyable for resource reasons
//Pretty deprecated

typedef unsigned int GLuint;

namespace ftec {
	class VBORenderable {
	public:
		struct VBORVertex {
			Vector3f position;
			Vector3f normal;
			Vector2f uv;
		};

	public://Should this even be used, like, ever?
		std::vector<VBORVertex> m_Vertices;
		unsigned int firstIndex;
		unsigned int lastIndex;
		GLuint m_Vbo;
	public:
		VBORenderable(unsigned int size);
		~VBORenderable();

		///Offset and amount in vertices
		void update(unsigned int offset, unsigned int amount);

		///Realocates m_Vertices.size() on the OpenGL side of things
		void realocate();
	};
}