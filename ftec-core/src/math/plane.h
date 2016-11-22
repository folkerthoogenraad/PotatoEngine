#pragma once

#include "vec3.h"
#include "triangle3.h"

namespace ftec {

	template <typename T>
	struct plane {
		vec3<T> direction;
		T offset;

		plane() {}
		plane(const triangle3<T> &triangle)
		{
			direction = triangle.normal();
			offset = -vec3<T>::dot(triangle.a, direction);
		}
		plane(const vec3<T> position, const vec3<T> direction) : direction(direction)
		{
			offset = -vec3<T>::dot(position, direction);
		}
		plane(const vec3<T> &dir, const T offset) : direction(dir), offset(offset) {}
		
		T distanceFrom(const vec3<T> &p)
		{
			return vec3<T>::dot(direction, p) + offset;
		}
		plane<T> &flip() 
		{
			direction = -direction;
			offset = -offset;
			return *this; 
		}
		plane<T> clone() const { return plane<T>(*this); }

		vec3<T> origin() const  
		{ 
			return direction * offset;
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

		T magnitude() const { return direction.magnitude(); }

		//TODO project
	};

	typedef plane<float> planef;
	typedef plane<double> planed;
	typedef plane<int> planei;
}