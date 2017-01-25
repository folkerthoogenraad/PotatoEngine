#pragma once

#include "Vector3.h"

namespace ftec {

	template <typename T>
	struct Ray3 {
		Vector3<T> origin;
		Vector3<T> direction;
	};
}