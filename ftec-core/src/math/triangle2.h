#pragma once

#include "collision.h"
#include "vec2.h"

namespace ftec {

	template<typename T>
	struct triangle2 {
		vec2<T> a;
		vec2<T> b;
		vec2<T> c;

		triangle2() {}
		triangle2(const vec2<T> &a, const vec2<T> &b, const vec2<T> &c)
			: a(a), b(b), c(c) {}

		bool hasVertex(vec2<T> v)
		{
			return a == v || b == v || c == v;
		}
		
		vec2<T> center()
		{
			return (a + b + c) / 3;
		}

		triangle2<T> &orient()
		{
			//Normals pointing outwards
			//Flip b and c if the winding is reversed
			if (edgeab().distanceFrom(c) > 0) {
				vec2<T> t = b;
				b = c;
				c = t;
			}

			return *this;
		}

		triangle2<T> clone()
		{
			return triangle2<T>(*this);
		}

		vec2<T> circumcenter()
		{
			return intersection(
				line2<T>(b, a).normal(),
				line2<T>(b, c).normal()
			);
		}

		circle<T> circumcircle()
		{
			auto center = circumcenter();
			return circle<T>(
				center,
				distance(a, center)
				);
		}

		bool isValid()
		{
			return intersects(
				line2<T>(b, a),
				line2<T>(b, c)
			);
		}

		line2<T> edgeab() const { return line2<T>(a, b); }
		line2<T> edgebc() const { return line2<T>(b, c); }
		line2<T> edgeca() const { return line2<T>(c, a); }
	};

	typedef triangle2<float> triangle2f;
	typedef triangle2<double> triangle2d;
	typedef triangle2<int> triangle2i;

}