#pragma once

#include "vec2.h"

namespace ftec {

	template<typename T>
	struct triangle {
		vec2<T> a;
		vec2<T> b;
		vec2<T> c;

		triangle() {}
		triangle(const vec2<T> &a, const vec2<T> &b, const vec2<T> &c)
			: a(a), b(b), c(c) {}

	};

	typedef triangle<float> trianglef;
	typedef triangle<double> triangled;
	typedef triangle<int> trianglei;

}