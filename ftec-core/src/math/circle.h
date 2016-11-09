#pragma once

namespace ftec {

	template<typename T>
	struct circle {
		vec2<T> center;
		T radius;

		circle() {}
		circle(const vec2<T> &c, T radius)
			: center(c), radius(radius) {}
	};

	typedef circle<float> circlef;
	typedef circle<double> circled;
	typedef circle<int> circlei;
}