#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

#include "Primitive.h"

namespace ftec {

	struct SpriteBatchVertex {
		Vector3f position;
		Vector2f uv;
		Color32 color;
		unsigned char texIndex;
	};

	class SpriteBatch {

	private:
		Primitive m_Primitive;

		bool m_Drawing;

		std::function<void()> m_RequestFlush;

		unsigned int m_Size;
		unsigned int m_VBOSize;

		// unsigned int m_VerticesVBO, m_UvsVBO, m_ColorsVBO;
		// std::vector<Vector3f> m_Vertices;
		// std::vector<Vector2f> m_Uvs;
		// std::vector<Color32> m_Colors;
		// Vector2f m_Uv;
		// Color32 m_Color;

		unsigned int m_VBO;

		std::vector<SpriteBatchVertex> m_Vertices;

		SpriteBatchVertex m_BufferVertex;

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

		void setRequestFlush(std::function<void()> func);

		bool isDrawing() { return m_Drawing; }

		inline size_t count() { return m_Vertices.size(); }
	};
}