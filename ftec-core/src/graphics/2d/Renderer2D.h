#pragma once

#include <vector>

#include "graphics/SpriteBatch.h"

namespace ftec {

	struct Drawable2D;
	
	//Forward declare mat3
	template<typename T> struct mat3; typedef mat3<float> mat3f;
	template<typename T> struct vec2; typedef vec2<float> vec2f;

	//New graphics API stuff
	class Renderer2D {
		SpriteBatch batch;
		std::vector<mat3f> m_TransformationStack;
	public:
		Renderer2D();
		~Renderer2D();

		void draw(Drawable2D &drawable);

		const mat3f &getTransformationMatrix() const;

		friend struct Transformation;
		friend struct Paint;
	private:
		void flush();
	};

	struct Paint {
	private:
		Renderer2D &m_Renderer;
		Primitive m_Primitive;
		float m_Depth;
	public:
		Paint(Renderer2D &r, Primitive primitive);
		~Paint();

		void vertex(float x, float y);
		void depth(float z);

		void color(const color32 &color);
		void uv(float u, float v);
	};

	struct Transformation {
	private:
		Renderer2D &m_Renderer;
		size_t m_MatrixIndex;

		void change();
	public:
		Transformation(Renderer2D &r);
		~Transformation();

		void translate(float x, float y);
		void scale(float x, float y);
		void rotate(float angle);
	};
	

}