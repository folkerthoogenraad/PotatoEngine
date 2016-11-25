#pragma once
#include "math/mat4.h"
#include "Layer.h"
#include <memory>
#include "RenderBuffer.h"
#include "Shader.h"

namespace ftec {
	class Camera {
	public:
		vec3f m_Position;

		//TODO add render target
		//TODO add ortho camera

		float m_Fov, m_AspectRatio, m_Near, m_Far;

		float m_Pitch, m_Yaw;

		Layer m_LayerMask;
		std::shared_ptr<RenderBuffer> m_RenderTarget;

		bool m_RenderToScreen = true; //render the renderbuffer to the screen after we are done with the backbuffer stuff
		std::shared_ptr<Shader> m_PostProcessingShader = nullptr;
	public:
		Camera() = default;
		Camera(float fov, float aspect, float near, float far);
		~Camera() = default;

		mat4f getProjectionMatrix() const;
		mat4f getViewMatrix() const;

		inline bool hasRenderTarget() const { return m_RenderTarget != 0; };

		bool operator==(const Camera &other);
		bool operator!=(const Camera &other);

	};
}