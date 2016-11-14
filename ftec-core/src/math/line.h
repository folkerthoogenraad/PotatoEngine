#pragma once

#include "vec2.h"

namespace ftec {
	template<typename T>
	struct line2 {
		vec2<T> a;
		vec2<T> b;

		line2() {}
		line2(const vec2<T> &a, const vec2<T> &b)
			: a(a), b(b) {}

		vec2<T> direction() const
		{
			return b - a;
		}

		vec2<T> perp() const
		{
			return vec2<T>::perp(direction());
		}

		const vec2<T> &origin() const
		{
			return a;
		}

		vec2<T> center() const
		{
			return (a + b) / 2.0f;
		}

		line2<T> normal() const
		{
			return line2<T>(center(), center() + perp());
		}

		T length() const
		{
			return distance(a, b);
		}
	};

	typedef line2<float> line2f;
	typedef line2<double> line2d;
	typedef line2<int> line2i;
}