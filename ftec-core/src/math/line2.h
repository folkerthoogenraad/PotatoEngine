#pragma once

#include "Vector2.h"

//TODO refactor this thing

namespace ftec {
	template<typename T>
	struct line2 {
		Vector2<T> a;
		Vector2<T> b;

		line2() {}
		line2(const Vector2<T> &a, const Vector2<T> &b)
			: a(a), b(b) {}

		Vector2<T> direction() const
		{
			return b - a;
		}

		Vector2<T> perp() const
		{
			return Vector2<T>::perp(direction());
		}

		const Vector2<T> &origin() const
		{
			return a;
		}

		Vector2<T> center() const
		{
			return (a + b) / (T)2.0;
		}

		line2<T> normal() const
		{
			Vector2<T> p = perp();
			return line2<T>(center(), center() + p);
		}

		//The distance from point to line in line units
		T distanceFrom(const Vector2<T> p)
		{
			return Vector2<T>::dot(p - a, perp());
		}

		T length() const
		{
			return distance(a, b);
		}

		line2<T> &translate(Vector2f v)
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