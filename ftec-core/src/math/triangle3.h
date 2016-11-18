#pragma once

#include "collision.h"
#include "line3.h"
#include "vec3.h"

namespace ftec {

	template<typename T>
	struct triangle3 {
		vec3<T> a;
		vec3<T> b;
		vec3<T> c;

		triangle3() {}
		triangle3(const vec3<T> &a, const vec3<T> &b, const vec3<T> &c)
			: a(a), b(b), c(c) {}

		bool hasVertex(vec3<T> v)
		{
			return a == v || b == v || c == v;
		}

		vec3<T> circumcenter()
		{
			return intersection(
				line3<T>(b, a).normal(),
				line3<T>(b, c).normal()
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
				line3<T>(b, a),
				line3<T>(b, c)
			);
		}

		triangle3<T> &flip() {
			std::swap(a, b);
			return *this;
		}

		line3<T> edgeab() const { return line3<T>(a, b); }
		line3<T> edgebc() const { return line3<T>(b, c); }
		line3<T> edgeca() const { return line3<T>(c, a); }

		template <typename T>
		static triangle3<T> unitTriangle()
		{
			return triangle3<T>(
				vec3<T>(-0.5f, 0, -1.f / 3.f*sqrt(0.75)),
				vec3<T>(0.5f, 0, -1.f / 3.f*sqrt(0.75)),
				vec3<T>(0, 0, 2.f/3.f*sqrt(0.75))
				);
		}
	};

	typedef triangle3<float> triangle3f;
	typedef triangle3<double> triangle3d;
	typedef triangle3<int> triangle3i;

}