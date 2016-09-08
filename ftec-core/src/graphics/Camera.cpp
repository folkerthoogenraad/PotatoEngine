#include "Camera.h"

namespace ftec {
	ftec::Camera::Camera(float fov, float aspect, float near, float)
		:fov(fov), aspect(aspect), near(near), far(far)
	{
	}

	mat4 ftec::Camera::getProjectionMatrix()
	{
		return mat4();
	}

	mat4 ftec::Camera::getViewMatrix()
	{
		return mat4();
	}
}
