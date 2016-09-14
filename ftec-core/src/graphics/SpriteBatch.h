#pragma once

#include "VBORenderable.h"
#include "math/vec3.h"
#include <memory>
#include "Material.h"
#include "Camera.h"

namespace ftec {

	class SpriteBatch {

	private:
		Material m_Material;
		Camera m_Camera;

		VBORenderable m_Vbo;
		unsigned int m_Index;
		bool m_Drawing;
	public:
		SpriteBatch();
		~SpriteBatch();

		void begin();
		void end();
		void flush();
		void vertex(vec3 position);
		void material(const Material&);
		void camera(const Camera&);
	};
}