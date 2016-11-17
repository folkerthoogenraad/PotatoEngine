#pragma once

namespace ftec {

	template<typename T>
	struct sphere {
		vec3<T> center;
		T radius;

		sphere() {}
		sphere(const vec3<T> &c, T radius)
			: center(c), radius(radius) {}
	};

	typedef sphere<float> spheref;
	typedef sphere<double> sphered;
	typedef sphere<int> spherei;
}