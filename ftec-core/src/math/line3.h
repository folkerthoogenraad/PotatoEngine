#pragma once

#include "vec3.h"

namespace ftec {

	template<typename T>
	struct mat4;

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
			return (a + b) / (T)2.0;
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

		T sqrmagnitude() const
		{
			return (b - a).sqrmagnitude();
		}
		T magnitude() const
		{
			return (b - a).magnitude();
		}

		line3<T> clone()
		{
			return line3<T>(*this);
		}

		line3<T> &flip()
		{
			T temp = a;
			a = b;
			b = temp;

			return *this;
		}
		line3<T> flipped() const
		{
			return clone().flip();
		}
	
		line3<T> &transform(const mat4<T> &m)
		{
			a = m * a;
			b = m * b;
			return *this;
		}
		line3<T> transformed(const mat4<T> &m) const
		{
			return clone().transform(m);
		}
	};

	typedef line3<float> line3f;
	typedef line3<double> line3d;
	typedef line3<int> line3i;
}