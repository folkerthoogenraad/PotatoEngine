#pragma once

#include "Vector2.h"
#include "Matrix2.h"

//TODO refactor this thing

namespace ftec {
	template<typename T>
	struct Line2 {
		Vector2<T> a;
		Vector2<T> b;

		Line2() {}
		Line2(const Vector2<T> &a, const Vector2<T> &b)
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

		Line2<T> normal() const
		{
			Vector2<T> p = perp();
			return Line2<T>(center(), center() + p);
		}

		//The distance from point to line in 'line units' (its complicated. If the line is normalized its just normal direction)
		T distanceFrom(const Vector2<T> &p)
		{
			return Vector2<T>::dot(p - a, perp());
		}

		T length() const
		{
			return distance(a, b);
		}

		Line2<T> &translate(Vector2f v)
		{
			a += v;
			b += v;

			return *this;
		}

		Line2<T> clone()
		{
			return Line2<T>(*this);
		}

		Line2<T> flipped()
		{
			return clone().flip();
		}

		Line2<T> &flip()
		{
			auto aa= a;
			a = b;
			b = aa;
			return *this;
		}
	};

	typedef Line2<float> Line2f;
	typedef Line2<double> Line2d;
	typedef Line2<int> Line2i;
	typedef Line2<long long> Line2ll;
}