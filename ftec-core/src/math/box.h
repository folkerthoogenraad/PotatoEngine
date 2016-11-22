#pragma once

#include "vec3.h"
#include "sphere.h"

namespace ftec {

	template<typename T>
	struct box {
		vec3<T> min;
		vec3<T> max;

		box() {}
		box(vec3<T> mn, vec3<T> mx) : min(mn), max(mx) {}

		vec3<T> center() const { return (min + max) / 2; }
		vec3<T> delta() const { return max - center(); }

		sphere<T> boundingSphere() const {
			return sphere<T>(
				(min + max) / 2.0f,
				(max - min).magnitude() / 2
				);
		}
	};

	typedef box<float> boxf;
	typedef box<double> boxd;
	typedef box<int> boxi;
}