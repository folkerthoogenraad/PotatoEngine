#pragma once

#include "Vector3.h"

namespace ftec {

	template<typename T>
	struct Matrix4;

	template<typename T>
	struct Line3 {
		Vector3<T> a;
		Vector3<T> b;

		Line3() {}
		Line3(const Vector3<T> &a, const Vector3<T> &b)
			: a(a), b(b) {}

		Vector3<T> direction() const
		{
			return b - a;
		}
		Vector3<T> perp() const
		{
			return Vector3<T>::perp(direction());
		}

		const Vector3<T> &origin() const
		{
			return a;
		}
		Vector3<T> center() const
		{
			return (a + b) / (T)2.0;
		}

		Line3<T> normal() const
		{
			Vector3<T> p = perp();
			return Line3<T>(center(), center() + p);
		}

		//The distance from point to line in line units
		T distanceFrom(const Vector3<T> p)
		{
			return Vector3<T>::dot(p - a, perp());
		}

		T sqrmagnitude() const
		{
			return (b - a).sqrmagnitude();
		}
		T magnitude() const
		{
			return (b - a).magnitude();
		}

		Line3<T> clone()
		{
			return Line3<T>(*this);
		}

		Line3<T> &flip()
		{
			T temp = a;
			a = b;
			b = temp;

			return *this;
		}
		Line3<T> flipped() const
		{
			return clone().flip();
		}
	
		Line3<T> &transform(const Matrix4<T> &m)
		{
			a = m * a;
			b = m * b;
			return *this;
		}
		Line3<T> transformed(const Matrix4<T> &m) const
		{
			return clone().transform(m);
		}
	};

	typedef Line3<float> Line3f;
	typedef Line3<double> Line3d;
	typedef Line3<int> Line3i;
}