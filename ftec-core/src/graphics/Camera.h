#pragma once

#include <memory>				//For std::shared_ptr

#include "math/Vector3.h"		//For camera position

namespace ftec {
	
	class RenderBuffer;
	class Shader;

	//Forward declare the matrix stuff
	template <typename T> struct Matrix4; typedef Matrix4<float> Matrix4f;
	typedef int Layer;

	class Camera {
	public:
		Vector3f m_Position;

		enum class Projection {
			PERSPECTIVE, ORTHOGONAL
		} m_Projection;

		//for perspective
		float m_Fov;

		//for orthogonal
		float m_Size = 1;

		float m_AspectRatio;
		float m_Near, m_Far;

		float m_Pitch, m_Yaw;

		Layer m_LayerMask;

		std::shared_ptr<RenderBuffer> m_RenderTarget;

		bool m_RenderToScreen = true; //render the renderbuffer to the screen after we are done with the backbuffer stuff
		std::shared_ptr<Shader> m_PostProcessingShader = nullptr;
	public:
		Camera();
		~Camera() = default;

		Matrix4f getProjectionMatrix() const;
		Matrix4f getViewMatrix() const;

		inline bool hasRenderTarget() const { return m_RenderTarget != nullptr; };

		bool operator==(const Camera &other);
		bool operator!=(const Camera &other);

		static Camera orthagonal(float size, float aspect, float near, float far);
		static Camera perspective(float fov, float aspect, float near, float far);

	};
}