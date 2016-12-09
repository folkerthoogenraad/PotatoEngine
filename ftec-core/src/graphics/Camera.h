#pragma once

#include <memory>
#include "Layer.h"

#include "math/Vector3.h"
#include "math/Matrix4.h"

namespace ftec {
	
	class RenderBuffer;
	class Shader;

	class Camera {
	public:
		Vector3f m_Position;
		
		//TODO add render target
		//TODO add ortho camera

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
		Camera() = default;
		Camera(float fov, float aspect, float near, float far);
		~Camera() = default;

		Matrix4f getProjectionMatrix() const;
		Matrix4f getViewMatrix() const;

		inline bool hasRenderTarget() const { return m_RenderTarget != 0; };

		bool operator==(const Camera &other);
		bool operator!=(const Camera &other);

	};
}