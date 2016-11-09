#pragma once

#include "vec2.h"

namespace ftec {
	template<typename T>
	struct line {
		vec2<T> origin;
		vec2<T> direction;

		line() {}
		line(const vec2<T> &origin, const vec2<T> &dir)
			: origin(origin), direction(dir) {}

	};

	typedef line<float> linef;
	typedef line<double> lined;
	typedef line<int> linei;
}