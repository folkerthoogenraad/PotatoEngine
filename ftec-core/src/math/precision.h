#pragma once

#include "math/Matrix2.h"
#include "math/Matrix3.h"

/*
For precision on computional geometry.
Floating point is currently not --really-- supported

Please refer to 
https://www.cs.cmu.edu/~quake/robust.html
*/
namespace ftec {

	template <typename T>
	struct Line2;
	template <typename T>
	struct Triangle2;
	template <typename T>
	struct Circle;

	template <typename T>
	T side(Line2<T> line, Vector2<T> p)
	{
		return Matrix2<T>({
			line.a.x - p.x, line.a.y - p.y,
			line.b.x - p.x, line.b.y - p.y
		}).determinant();
	}

	template <typename T>
	T incircle(Circle<T> c, Vector2<T> p)
	{
		Vector2<T> r = p - c.center;

		return r.sqrmagnitude() - c.radius * c.radius;
	}

	template <typename T>
	T sqr(T a)
	{
		return a * a;
	}

	template <typename T>
	T incircle(Triangle2<T> t, Vector2<T> p)
	{
		t.a -= p;
		t.b -= p;
		t.c -= p;

		return Matrix3<T>({
			t.a.x, t.a.y, sqr(t.a.x) + sqr(t.a.y),
			t.b.x, t.b.y, sqr(t.b.x) + sqr(t.b.y),
			t.c.x, t.c.y, sqr(t.c.x) + sqr(t.c.y)
		}).determinant();
	}
}