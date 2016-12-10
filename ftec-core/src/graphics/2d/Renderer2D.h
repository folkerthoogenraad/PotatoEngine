#pragma once

#include <vector>

#include "graphics/SpriteBatch.h"

namespace ftec {

	class Texture;
	class Shader;

	struct Drawable2D;
	
	//Forward declare Matrix3
	template<typename T> struct Matrix3; typedef Matrix3<float> Matrix3f;
	template<typename T> struct Vector2; typedef Vector2<float> Vector2f;

	//New graphics API stuff
	class Renderer2D {
		SpriteBatch batch;
		std::vector<Matrix3f> m_TransformationStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_WhiteTexture;

		std::shared_ptr<Texture> m_CurrentTexture;

		int m_ModelLocation;
		int m_ViewLocation;
		int m_ProjectionLocation;

		bool m_Drawing = false;
	public:
		Renderer2D();
		~Renderer2D();

		void draw(Drawable2D &drawable);

		const Matrix3f &getTransformationMatrix() const;

		friend struct Transformation;
		friend struct Paint;
	private:
		void flush();
	};

	struct Paint {
	private:
		Renderer2D &m_Renderer;
		Primitive m_Primitive;
		float m_Depth = 0;
	public:
		Paint(Renderer2D &r, Primitive primitive);
		~Paint();

		void vertex(float x, float y);
		void depth(float z);

		void color(Color32 color);
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