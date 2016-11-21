#pragma once

#include "vec2.h"
#include "circle.h"
#include "collision.h"
#include <iostream>

namespace ftec {
	
	template <typename T>
	struct rect {
		rect() = default;
		
		template<typename S>
		rect(const rect<S> r) : position(r.position), size(r.size) {};
		rect(T x, T y, T w, T h) : position(x,y), size(w,h) {};

		//TODO change to MIN and MAX position (possibly?)
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

		vec2<T> topleft() const { return vec2<T>(left(), top()); }
		vec2<T> topright() const { return vec2<T>(right(), top()); }
		vec2<T> bottomleft() const { return vec2<T>(left(), bottom()); }
		vec2<T> bottomright() const { return vec2<T>(right(), bottom()); }

		vec2<T> center() const { return vec2<T>(position.x + size.x / 2, position.y + size.y / 2); }
		vec2<T> centerLeft() const { return vec2<T>(position.x, position.y + size.y / 2); }
		vec2<T> centerRight() const { return vec2<T>(position.x + size.x, position.y + size.y / 2); }
		
		circle<T> boundingCircle() const { return circle<T>(center(), distance(center(), bottomright())); }

		bool contains(vec2<T> v) { return !(v.x < left() || v.x > right() || v.y < top() || v.y > bottom()); };


		friend std::ostream& operator<<(std::ostream &out, const rect<T> &r)
		{
			return out << "(" << r.x() << ", " << r.y() << ", " << r.width() << ", " << r.height() << ")";
		}
	};

	typedef rect<float> rectf;
	typedef rect<int> recti;
	typedef rect<double> rectd;
}
