#include "Camera.h"

namespace ftec {
	ftec::Camera::Camera(float fov, float aspect, float near, float far)
		:m_Fov(fov), m_AspectRatio(aspect), m_Near(near), m_Far(far), m_Pitch(0), m_Yaw(0)
	{
		
	}

	mat4 ftec::Camera::getProjectionMatrix() const
	{
		return mat4::perspective(m_Fov, m_AspectRatio, m_Near, m_Far) * mat4::translation(vec3(0, 0, 1));
	}

	mat4 ftec::Camera::getViewMatrix() const
	{
		return mat4::rotationX(m_Pitch) * mat4::rotationY(m_Yaw) * mat4::translation(-m_Position);// *mat4::rotationX(m_Pitch);// *mat4::rotation(m_Pitch, vec3(1, 0, 0));// ;
	}
	bool Camera::operator==(const Camera & other)
	{
		return false; //TODO implement this
	}
	bool Camera::operator!=(const Camera & other)
	{
		return !(*this == other);
	}
}
