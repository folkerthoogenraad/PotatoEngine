#pragma once
#include "math/mat4.h"
#include "Layer.h"

namespace ftec {
	class Camera {
	public:
		vec3 m_Position;

		//TODO add render target
		//TODO add ortho camera

		float m_Fov, m_AspectRatio, m_Near, m_Far;

		float m_Pitch, m_Yaw;

		int m_LayerMask;
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