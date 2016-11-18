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

		sphere<T> boundingSphere() {
			return sphere<T>(
				(min + max) / 2.0f,
				(max - min).magnitude() / 2.0f
				);
		}
	};

	typedef box<float> boxf;
	typedef box<double> boxd;
	typedef box<int> boxi;
}