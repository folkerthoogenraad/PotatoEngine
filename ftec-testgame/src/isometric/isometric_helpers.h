#pragma once

#include "math/Vector2.h"
#include "math/Vector3.h"

namespace ftec {

	Vector2f isometricTransform(Vector3f input)
	{
		return Vector2f(
			(input.x - input.z) * 1,
			(input.x + input.z) * 0.5f + input.y
		);
	}

}