#pragma once
#include "math/mat4.h"

namespace ftec {
	class Camera {
	private:
		vec3 position;

		//TODO figure out if this is a great idea (hint: its not)
		float pitch;
		float yaw;

		float fov, aspect, near, far;

	public:
		Camera(float fov, float aspect, float near, float far);
		~Camera() = default;

		mat4 getProjectionMatrix();
		mat4 getViewMatrix();

	};
}