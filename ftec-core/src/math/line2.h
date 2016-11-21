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
			vec2<T> p = perp();
			return line2<T>(center(), center() + p);
		}

		//The distance from point to line in line units
		T distanceFrom(const vec2<T> p)
		{
			return vec2<T>::dot(p - a, perp());
		}

		T length() const
		{
			return distance(a, b);
		}

		line2<T> &translate(vec2f v)
		{
			a += v;
			b += v;

			return *this;
		}

		line2<T> clone()
		{
			return line2<T>(*this);
		}

		line2<T> flipped()
		{
			return clone().flip();
		}

		line2<T> &flip()
		{
			auto aa= a;
			a = b;
			b = aa;
			return *this;
		}
	};

	typedef line2<float> line2f;
	typedef line2<double> line2d;
	typedef line2<int> line2i;
}