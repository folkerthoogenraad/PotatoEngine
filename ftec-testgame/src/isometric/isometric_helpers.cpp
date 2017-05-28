#include "isometric_helpers.h"

namespace ftec {

	Matrix3f ftec::getIsometricTransformationMatrix(Vector3f position, bool flat)
	{
		if (!flat){
			return Matrix3f({
				1,0,position.x,
				0,1,position.y + position.z,
				0,0,position.y
			});
		}

		else {
			return Matrix3f({
				1,0,position.x,
				0,1,position.y + position.z,
				0,1,position.y - position.z
			});
		}
	}

}
