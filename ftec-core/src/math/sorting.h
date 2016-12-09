#pragma once

#include <vector>
#include <algorithm>

namespace ftec {

	template <typename T>
	struct Vector2;

	template <typename T>
	void polarsort(std::vector<Vector2<T>> &v, const Vector2<T> center)
	{
		std::sort(v.begin(), v.end(),
			[&center](const Vector2<T> &a, const Vector2<T> &b) {
			Vector2<T> aa = (a - center).normalize();
			Vector2<T> bb = (b - center).normalize();
			return atan2(aa.y, aa.x) < atan2(bb.y, bb.x);
		});
	}
}