#pragma once

#define PI 3.141592654f

//TODO refactor this whole codebase thing

#include "vec2.h"

// ):
#include <math.h>

namespace ftec {

	template <typename T>
	struct vec3;
	template <typename T>
	struct vec4;


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
			vec2f p1, p2;
		public:
			//Default curve is stolen from google material stuff
			CubicBezier(const vec2f &p1 = vec2f(.4f, 0.f), const vec2f &p2 = vec2f(.2f, 1.f)) : p1(p1), p2(p2) {};

			float interpolate(float x) const override;
		};
	}

	template <typename T>
	T tween(T a, T b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template <typename T>
	vec2<T> tween(vec2<T> a, vec2<T> b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template <typename T>
	vec3<T> tween(vec3<T> a, vec3<T> b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template <typename T>
	vec4<T> tween(vec4<T> a, vec4<T> b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}
}