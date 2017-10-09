#pragma once

#define PI 3.141592654f

//TODO refactor this whole codebase thing

#include "Vector2.h"

// ):
#include <math.h>

namespace ftec {

	template <typename T>
	struct Vector3;
	template <typename T>
	struct Vector4;


	namespace curves {

		struct Base {
			virtual float interpolate(float x) const = 0;
		};

		struct Linear : public Base{
			float interpolate(float x) const override { return x; }
		};

		struct Quadratic : public Base {
			float interpolate(float x) const override { return x*x; }
		};

		struct SquareRoot : public Base {
			float interpolate(float x) const override { return sqrtf(x); }
		};

		struct Cosine : public Base {
			float interpolate(float x) const override { return (1.f - cosf(x * PI)) / 2.f; }
		};

		struct CubicBezier : public Base {
		private:
			Vector2f p1, p2;
		public:
			//Default curve is stolen from google material stuff
			CubicBezier(const Vector2f &p1 = Vector2f(.4f, 0.f), const Vector2f &p2 = Vector2f(.2f, 1.f)) : p1(p1), p2(p2) {};

			float interpolate(float x) const override;
		};

		// TODO move this to a better namespace with shapes or something
		struct VCubicBezier{
		public:
			Vector2f p0, p1, p2, p3;
		public:
			// Also todo optimize this.
			Vector2f interpolate(float x) const;
		};
	}

	template <typename T>
	T tween(T a, T b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template <typename T>
	Vector2<T> tween(Vector2<T> a, Vector2<T> b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template <typename T>
	Vector3<T> tween(Vector3<T> a, Vector3<T> b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template <typename T>
	Vector4<T> tween(Vector4<T> a, Vector4<T> b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}
}