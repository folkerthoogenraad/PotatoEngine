#pragma once

#include <gl/glew.h>
#include "VBORenderable.h"
#include "math/vec3.h"

namespace ftec {
	class SpriteBatch {

	private:
		VBORenderable m_Vbo;
		unsigned int index;
	public:
		SpriteBatch();
		~SpriteBatch();

		void begin();
		void end();
		void flush();
		void vertex(vec3 position);
	};
}