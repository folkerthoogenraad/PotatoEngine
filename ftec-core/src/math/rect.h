#pragma once

#include "vec2.h"
namespace ftec {
	
	template <typename T>
	struct rect2 {
		rect2() = default;
		rect2(T x, T y, T w, T h) : position(x,y), size(w,h) {};

		vec2<T> position;
		vec2<T> size;

		T &x() { return position.x; }
		T &y() { return position.y; }
		T &width() { return size.x; }
		T &height() { return size.y; }

		T x() const { return position.x; }
		T y() const { return position.y; }
		T width() const { return size.x; }
		T height() const { return size.y; }

		T left() const { return position.x; }
		T right() const { return position.x + size.x; }
		T top() const { return position.y; }
		T bottom() const { return position.y + size.y; }

	};

	typedef rect2<float> rect2f;
	typedef rect2<int> rect2i;
	typedef rect2<double> rect2d;
}
