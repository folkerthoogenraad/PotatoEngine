#pragma once

#include <memory>
#include <vector>

#include "math/Vector2.h"
#include "math/Vector4.h"

#include "Primitive.h"

namespace ftec {

	template<typename T> struct Vector3; typedef Vector3<float> Vector3f;

	class SpriteBatch {

	private:
		Primitive m_Primitive;

		bool m_Drawing;

		Vector2f m_Uv;
		Color32 m_Color;

		unsigned int m_VerticesVBO, m_UvsVBO, m_ColorsVBO;
		unsigned int m_Size;
		unsigned int m_VBOSize;

		std::vector<Vector3f> m_Vertices;
		std::vector<Vector2f> m_Uvs;
		std::vector<Color32> m_Colors;

		float m_Depth = 0;
	public:
		SpriteBatch();
		~SpriteBatch();

		void begin(Primitive primitive);
		void flush();
		void end();

		void depth(float d);
		float depth() const { return m_Depth; };

		void vertex(Vector3f position);

		void vertex(Vector2f position); //TODO check if this is needed
		void color(Color32 color);
		void uv(Vector2f uv);

		Primitive primitive();

		bool isDrawing() { return m_Drawing; }

		inline size_t count() { return m_Vertices.size(); }
	};
}