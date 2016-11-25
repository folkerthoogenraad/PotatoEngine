#pragma once

#include <vector>
#include <algorithm>

namespace ftec {

	template <typename T>
	struct vec2;

	template <typename T>
	void polarsort(std::vector<vec2<T>> &v, const vec2<T> center)
	{
		std::sort(v.begin(), v.end(),
			[&center](const vec2<T> &a, const vec2<T> &b) {
			vec2<T> aa = (a - center).normalize();
			vec2<T> bb = (b - center).normalize();
			return atan2(aa.y, aa.x) < atan2(bb.y, bb.x);
		});
	}
}