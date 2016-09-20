#pragma once

#include "RenderBuffer.h"
#include "math/math.h"

#define SHADOW_RESOLUTION 1024

namespace ftec {
	//TODO class LightWorld or something LightSpace
	class Light {
	public:
		vec3 m_Direction = vec3(-1.0,-1.0,-1.0).normalize();
		bool m_Enabled = true;
	private:
		bool m_ShadowsEnabled = false;
		std::shared_ptr<RenderBuffer> m_ShadowMap;
	public:
		Light() = default;
		~Light() = default;

		void setShadowsEnabled(bool enabled);

		inline bool isShadowsEnabled() const { return m_ShadowsEnabled; };
		inline std::shared_ptr<RenderBuffer> getShadowBuffer() const { return m_ShadowMap; };
		mat4 getShadowMatrix(const vec3 &position = vec3()) const;

		static inline Light defaultLight() { return Light(); };
	};
}