#pragma once

#include "Vector2.h"

namespace ftec {

	template <typename T>
	struct Vector2;
	template <typename T>
	struct Circle;
	
	template <typename T>
	struct Rectangle {
		Rectangle() = default;
		
		template<typename S>
		Rectangle(const Rectangle<S> r) : position(r.position), size(r.size) {};
		Rectangle(T x, T y, T w, T h) : position(x,y), size(w,h) {};

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
		
		Circle<T> boundingCircle() const { return Circle<T>(center(), (bottomright() - center()).magnitude()); }

		bool contains(Vector2<T> v) { return !(v.x < left() || v.x > right() || v.y < top() || v.y > bottom()); };

		//TODO find the right names for these "constructors"
		static Rectangle<T> centered(T x, T y, T width, T height)
		{
			return std::move(Rectangle<T>(
				x - width / (T)2,
				y - height / (T)2,
				width, height
				));
		}
	};

	typedef Rectangle<float> Rectanglef;
	typedef Rectangle<int> Rectanglei;
	typedef Rectangle<double> Rectangled;
}
