#include "Camera.h"

namespace ftec {
	Camera::Camera(float fov, float aspect, float near, float far)
		:m_Fov(fov), m_AspectRatio(aspect), m_Near(near), m_Far(far), m_Pitch(0), m_Yaw(0), m_LayerMask(LAYER_ALL), m_RenderToScreen(true), m_PostProcessingShader(nullptr)
	{
		
	}

	mat4f ftec::Camera::getProjectionMatrix() const
	{
		return mat4f::perspective(m_Fov, m_AspectRatio, m_Near, m_Far);// *mat4f::translation(vec3(0, 0, 1));
	}

	mat4f ftec::Camera::getViewMatrix() const
	{
		return mat4f::rotationX(m_Pitch) * mat4f::rotationY(m_Yaw) * mat4f::translation(-m_Position);// *mat4f::rotationX(m_Pitch);// *mat4f::rotation(m_Pitch, vec3(1, 0, 0));// ;
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
