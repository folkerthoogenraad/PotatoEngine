#pragma once

#include "Vector2.h"

namespace ftec {

	template <typename T>
	struct Vector2;
	template <typename T>
	struct circle;
	
	template <typename T>
	struct rect {
		rect() = default;
		
		template<typename S>
		rect(const rect<S> r) : position(r.position), size(r.size) {};
		rect(T x, T y, T w, T h) : position(x,y), size(w,h) {};

		//TODO change to MIN and MAX position (possibly?)
		Vector2<T> position;
		Vector2<T> size;

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

		Vector2<T> topleft() const { return Vector2<T>(left(), top()); }
		Vector2<T> topright() const { return Vector2<T>(right(), top()); }
		Vector2<T> bottomleft() const { return Vector2<T>(left(), bottom()); }
		Vector2<T> bottomright() const { return Vector2<T>(right(), bottom()); }

		Vector2<T> center() const { return Vector2<T>(position.x + size.x / 2, position.y + size.y / 2); }
		Vector2<T> centerLeft() const { return Vector2<T>(position.x, position.y + size.y / 2); }
		Vector2<T> centerRight() const { return Vector2<T>(position.x + size.x, position.y + size.y / 2); }
		
		circle<T> boundingCircle() const { return circle<T>(center(), (bottomright() - center()).magnitude()); }

		bool contains(Vector2<T> v) { return !(v.x < left() || v.x > right() || v.y < top() || v.y > bottom()); };
	};

	typedef rect<float> rectf;
	typedef rect<int> recti;
	typedef rect<double> rectd;
}
