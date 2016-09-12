#pragma once
#include "math/mat4.h"

namespace ftec {
	class Camera {
	public:
		vec3 m_Position;

		float m_Fov, m_AspectRatio, m_Near, m_Far;

		float m_Pitch, m_Yaw;
	public:
		Camera() = default;
		Camera(float fov, float aspect, float near, float far);
		~Camera() = default;

		mat4 getProjectionMatrix() const;
		mat4 getViewMatrix() const;

		bool operator==(const Camera &other);
		bool operator!=(const Camera &other);

	};
}