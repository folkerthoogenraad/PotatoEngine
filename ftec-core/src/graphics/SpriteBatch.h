#pragma once

#include "VBORenderable.h"

#include "math/vec3.h"
#include "math/vec4.h"

#include "Material.h"
#include "Camera.h"

#include <memory>
#include <vector>

typedef unsigned int GLuint;

namespace ftec {

	enum class Primitive {
		LINES,
		QUADS,
		TRIANGLES,
		POINTS
	};

	class SpriteBatch {

	private:
		Primitive m_Primitive;

		bool m_Drawing;

		vec2f m_Uv;
		color32 m_Color;

		GLuint m_VerticesVBO, m_UvsVBO, m_ColorsVBO;
		unsigned int m_Size;
		unsigned int m_VBOSize;

		std::vector<vec3f> m_Vertices;
		std::vector<vec2f> m_Uvs;
		std::vector<color32> m_Colors;
	public:
		SpriteBatch();
		~SpriteBatch();

		void begin(Primitive primitive);
		void end();

		void vertex(const vec3f &position);
		void vertex(const vec2f &position);
		void color(const color32 &color);
		void uv(const vec2f &uv);

		bool isDrawing() { return m_Drawing; }

		inline size_t count() { return m_Vertices.size(); }
	};
}