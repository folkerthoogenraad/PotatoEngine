#pragma once

#include "collision.h" //TODO not need this

#include "Vector2.h"

namespace ftec {

	template<typename T>
	struct Triangle2 {
		Vector2<T> a;
		Vector2<T> b;
		Vector2<T> c;

		Triangle2() {}
		Triangle2(const Vector2<T> &a, const Vector2<T> &b, const Vector2<T> &c)
			: a(a), b(b), c(c) {}

		bool hasVertex(Vector2<T> v)
		{
			return a == v || b == v || c == v;
		}
		
		Vector2<T> center()
		{
			return (a + b + c) / 3;
		}

		Triangle2<T> &orient()
		{
			//Normals pointing outwards
			//Flip b and c if the winding is reversed
			if (edgeab().distanceFrom(c) > 0) {
				Vector2<T> t = b;
				b = c;
				c = t;
			}

			return *this;
		}

		Triangle2<T> clone()
		{
			return Triangle2<T>(*this);
		}

		Vector2<T> circumcenter()
		{
			return intersect(
				Line2<T>(b, a).normal(),
				Line2<T>(b, c).normal()
			).result;
		}

		Circle<T> circumcircle()
		{
			auto center = circumcenter();
			return Circle<T>(
				center,
				distance(a, center)
				);
		}

		bool isValid()
		{
			return intersects(
				Line2<T>(b, a),
				Line2<T>(b, c)
			);
		}

		Line2<T> edgeab() const { return Line2<T>(a, b); }
		Line2<T> edgebc() const { return Line2<T>(b, c); }
		Line2<T> edgeca() const { return Line2<T>(c, a); }
	};

	typedef Triangle2<float> Triangle2f;
	typedef Triangle2<double> Triangle2d;
	typedef Triangle2<int> Triangle2i;

}