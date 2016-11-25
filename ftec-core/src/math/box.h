#pragma once

#include "vec3.h"

namespace ftec {

	template<typename T>
	struct sphere;

	template<typename T>
	struct box {
		vec3<T> min;
		vec3<T> max;

		box() {}
		box(vec3<T> mn, vec3<T> mx) : min(mn), max(mx) {}

		vec3<T> center() const { return (min + max) / 2; }
		vec3<T> delta() const { return max - center(); }

		box<T> clone() const { return box<T>(*this); }
		sphere<T> boudingsphere() const {
			return sphere<T>(
				(min + max) / 2,
				(max - min).magnitude() / 2
				);
		}
	};

	typedef box<float> boxf;
	typedef box<double> boxd;
	typedef box<int> boxi;
}