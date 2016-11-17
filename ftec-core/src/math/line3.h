#pragma once
#include "vec3.h"

namespace ftec {
	template<typename T>
	struct line3 {
		vec3<T> a;
		vec3<T> b;

		line3() {}
		line3(const vec3<T> &a, const vec3<T> &b)
			: a(a), b(b) {}

		vec3<T> direction() const
		{
			return b - a;
		}

		vec3<T> perp() const
		{
			return vec3<T>::perp(direction());
		}

		const vec3<T> &origin() const
		{
			return a;
		}

		vec3<T> center() const
		{
			return (a + b) / 2.0f;
		}

		line3<T> normal() const
		{
			vec3<T> p = perp();
			return line3<T>(center(), center() + p);
		}

		//The distance from point to line in line units
		T distanceFrom(const vec3<T> p)
		{
			return vec3<T>::dot(p - a, perp());
		}

		T length() const
		{
			return distance(a, b);
		}

		line3<T> clone()
		{
			return line3<T>(*this);
		}

	};

	typedef line3<float> line3f;
	typedef line3<double> line3d;
	typedef line3<int> line3i;
}