#pragma once

#include "VBORenderable.h"
#include "math/vec3.h"
#include <memory>
#include "Material.h"
#include "Camera.h"
#include <vector>

typedef unsigned int GLuint;

namespace ftec {

	enum class Primitive {
		LINES,
		QUADS,
		TRIANGLES
	};

	class SpriteBatch {

	private:
		Primitive m_Primitive;

		bool m_Drawing;

		vec2f m_Uv;
		color32 m_Color;

		GLuint m_VerticesVBO, m_UvsVBO, m_ColorsVBO;
		unsigned int m_Size;

		std::vector<vec3f> m_Vertices;
		std::vector<vec2f> m_Uvs;
		std::vector<color32> m_Colors;
	public:
		SpriteBatch();
		~SpriteBatch();

		void begin(Primitive primitive);
		void end();

		void vertex(const vec3f &position);
		void color(const color32 &color);
		void uv(const vec2f &uv);

		bool isDrawing() { return m_Drawing; }

		inline int count() { return m_Vertices.size(); }
	};
}