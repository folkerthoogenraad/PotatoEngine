#pragma once

#define PI 3.141592654f

#include "vec2.h"

namespace ftec {
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
}