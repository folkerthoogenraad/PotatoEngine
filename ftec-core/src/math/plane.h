#pragma once

#include "vec3.h"

namespace ftec {

	template <typename T>
	struct triangle3;
	template <typename T>
	struct line3;
	template <typename T>
	struct plane;

	template <typename T>
	struct plane {
		//Ax + By + Cz + D
		vec3<T> direction;
		T offset;

		plane() {}
		explicit plane(const triangle3<T> &triangle)
		{
			direction = triangle.normal();
			offset = -vec3<T>::dot(triangle.a, direction);
		}
		plane(const vec3<T> position, const vec3<T> direction) : direction(direction)
		{
			offset = -vec3<T>::dot(position, direction);
		}
		plane(const vec3<T> &dir, const T &offset) : direction(dir), offset(offset) {}
		
		T distanceFrom(const vec3<T> &p) const
		{
			float c = vec3<T>::dot(direction, direction);
			float r = vec3<T>::dot(direction, p);

			//ax + by + cz + d = 0
			//ax + by + cz = -d

			return (-offset - r) / c;
		}
		plane<T> &flip() 
		{
			direction = -direction;
			offset = -offset;
			return *this; 
		}
		plane<T> clone() const { return plane<T>(*this); }
		plane<T> flipped() const { return clone().flip(); }

		vec3<T> origin() const  
		{
			return direction * distanceFrom(vec3f());
		}

		plane<T> &normalize() 
		{
			T mag = direction.magnitude();
			direction /= mag;
			offset *= mag;

			return *this;
		}
		plane<T> normalized() const
		{
			return clone().normalize();
		}

#if 0
		//Intersects two planes. IfV the planes are perpendicular, the line has a length of 0
		line3<T> intersection(const plane<T> &other) const
		{
			vec3<T> dir = vec3<T>::cross(other.direction, direction);

			//Perform a line intersection with the other plane
			line3<T> line(origin(), origin() + vec3<T>::cross(dir, direction));

			vec3<T> o = other.intersection(line);

			return line3<T>(o, o + dir);
		}
		
		//Intersects a line and a plane, returns vec3<T>::nan if there is no intersection
		vec3<T> intersection(const line3<T> &line) const
		{
			vec3<T> lineDir = line.direction();

			T directionalDot = vec3<T>::dot(lineDir, direction);

			if (directionalDot == 0)
				return vec3<T>::nan();

			T planerDot = -(vec3<T>::dot(direction, line.a) + offset);

			T result = planerDot / directionalDot;

			return line.a + lineDir * result;
		}

#endif
		T magnitude() const { return direction.magnitude(); }

		vec3<T> project(const vec3<T> &p) const
		{
			float t = distanceFrom(p);
			return p + direction * t;
		}
	};

	typedef plane<float> planef;
	typedef plane<double> planed;
	typedef plane<int> planei;
}