#pragma once

#include <iostream>

#define LOG(message) std::cout << message << std::endl
#define LOG_ERROR(message) std::cerr << "(" << __FILE__ << ":" << __LINE__ << ")" << message << std::endl

#define LOG_DEBUG(message) std::cout << "(" << __FILE__ << ":" << __LINE__ << ")" << message << std::endl

#define TERMINATE(message) std::cerr << "SYSTEM ERROR:" << std::endl << message << std::endl << "Press any key to continue..."; std::cin.get(); exit(-1)
#define WAIT() std::cout << "Press any key to continue... "; std::cin.get()

namespace ftec {

	//-------------------------------------------------------------------
	// Vectors
	//-------------------------------------------------------------------
	template <typename T>
	struct vec2;
	template <typename T>
	struct vec3;
	template <typename T>
	struct vec4;
	
	template <typename T>
	std::ostream& operator<<(std::ostream& left, const vec2<T>& right)
	{
		return left << "(" << right.x << ", " << right.y << ")";
	}
	template <typename T>
	std::ostream& operator<<(std::ostream& left, const vec3<T>& right)
	{
		return left << "(" << right.x << ", " << right.y << ", " << right.z << ")";
	}
	template <typename T>
	std::ostream& operator<<(std::ostream& left, const vec4<T>& right)
	{
		return left << "(" << right.x << ", " << right.y << ", " << right.z << ", " << right.w << ")";
	}


	//-------------------------------------------------------------------
	// Shapes
	//-------------------------------------------------------------------

	template <typename T>
	struct rect;

	template <typename T>
	std::ostream& operator<<(std::ostream &out, const rect<T> &r)
	{
		return out << "(" << r.x() << ", " << r.y() << ", " << r.width() << ", " << r.height() << ")";
	}

	//-------------------------------------------------------------------
	// Matrices
	//-------------------------------------------------------------------

	template <typename T>
	struct mat4;
	template <typename T>
	struct mat3;

	template <typename T>
	std::ostream& operator<<(std::ostream& left, const mat4<T>& right)
	{
		for (int row = 0; row < 4; ++row) {
			left << "[";
			for (int column = 0; column < 4; ++column) {
				left << right.elements[column + row * 4];
				if (column != 3)
					left << ", ";
			}
			left << "]" << std::endl;
		}

		return left;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream & left, const mat3<T> & right)
	{
		for (int row = 0; row < 3; ++row) {
			left << "[";
			for (int column = 0; column < 3; ++column) {
				left << right.el(column, row);// [column + row * 3];
				if (column != 2)
					left << ", ";
			}
			left << "]" << std::endl;
		}

		return left;
	}
}