#pragma once

#include "RenderBuffer.h"

//TODO remove these if possible
#include "math/vec4.h"
#include "math/vec3.h"
#include "math/mat4.h"

#define SHADOW_RESOLUTION 1024

namespace ftec {
	//TODO class LightWorld or something LightSpace
	class Light {
	public:
		vec3f m_Direction = vec3f(-1.0, -1.0, -1.0).normalize();
		color32 m_Color = color32::white();

		//Currently not working correctly with PBR ( ~ish :') )
		float m_Intensity = 1.f; 
	private:
		bool m_ShadowsEnabled = false;
		std::shared_ptr<RenderBuffer> m_ShadowMap;
	public:
		Light() = default;
		~Light() = default;

		void setShadowsEnabled(bool enabled);

		inline bool isShadowsEnabled() const { return m_ShadowsEnabled; };
		inline std::shared_ptr<RenderBuffer> getShadowBuffer() const { return m_ShadowMap; };
		mat4f getShadowMatrix(const vec3f &position = vec3f()) const;

		//This is too stupid and should not even exist
		static inline Light defaultLight() { return Light(); };
	};
}