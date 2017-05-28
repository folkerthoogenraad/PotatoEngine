#pragma once

#include "math/Matrix3.h"
#include "math/Vector3.h"

namespace ftec {

	Matrix3f getIsometricTransformationMatrix(Vector3f position, bool flat = false);

}