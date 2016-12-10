#include "Camera.h"

#include "Layer.h"
#include "math/Matrix4.h"

namespace ftec {
	/*Camera::Camera(float fov, float aspect, float near, float far)
		:m_Fov(fov), m_AspectRatio(aspect), m_Near(near), m_Far(far), m_Pitch(0), m_Yaw(0), m_LayerMask(LAYER_ALL), m_RenderToScreen(true), m_PostProcessingShader(nullptr), m_Projection(Projection::PERSPECTIVE)
	{ }*/

	Camera::Camera()
		:m_Position(),
		m_Projection(Projection::PERSPECTIVE),
		m_Fov(60.0f),
		m_Size(1.0f),
		m_AspectRatio(4.0f / 3.0f),
		m_Near(0.01f),
		m_Far(1000.0f),
		m_Pitch(0.0f),
		m_Yaw(0.0f),
		m_LayerMask(LAYER_ALL),
		m_RenderTarget(nullptr),
		m_RenderToScreen(false),
		m_PostProcessingShader(nullptr)
	{ }

	Matrix4f ftec::Camera::getProjectionMatrix() const
	{
		if (m_Projection == Projection::PERSPECTIVE)
			return Matrix4f::perspective(m_Fov, m_AspectRatio, m_Near, m_Far);
		else
			return Matrix4f::orthographic(-m_Size * m_AspectRatio, m_Size * m_AspectRatio, -m_Size, m_Size, m_Near, m_Far);
	}

	Matrix4f ftec::Camera::getViewMatrix() const
	{
		//TODO quaternion class and stuff
		return Matrix4f::rotationX(m_Pitch) * Matrix4f::rotationY(m_Yaw) * Matrix4f::translation(-m_Position);
	}
	bool Camera::operator==(const Camera & other)
	{
		return false; //TODO implement this
	}
	bool Camera::operator!=(const Camera & other)
	{
		return !(*this == other);
	}
	Camera Camera::orthagonal(float size, float aspect, float near, float far)
	{
		Camera camera = Camera();
		camera.m_Projection = Camera::Projection::ORTHOGONAL;
		camera.m_Size = size;
		camera.m_AspectRatio = aspect;
		camera.m_Near = near;
		camera.m_Far = far;

		return std::move(camera);
	}
	Camera Camera::perspective(float fov, float aspect, float near, float far)
	{
		Camera camera = Camera();

		camera.m_Projection = Camera::Projection::PERSPECTIVE;
		camera.m_Fov = fov;
		camera.m_AspectRatio = aspect;
		camera.m_Near = near;
		camera.m_Far = far;

		return std::move(camera);
	}
}
