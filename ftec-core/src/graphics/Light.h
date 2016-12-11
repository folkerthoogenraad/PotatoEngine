#pragma once

#include "RenderBuffer.h"

//TODO remove these if possible
#include "math/Vector4.h"
#include "math/Vector3.h"
#include "math/Matrix4.h"

#define SHADOW_RESOLUTION 1024

namespace ftec {
	//TODO class LightWorld or something LightSpace
	class Light {
	public:
		Vector3f m_DiRectangleion = Vector3f(-1.0, -1.0, -1.0).normalize();
		Color32 m_Color = Color32::white();

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
		Matrix4f getShadowMatrix(const Vector3f &position = Vector3f()) const;

		//This is too stupid and should not even exist
		static inline Light defaultLight() { return Light(); };
	};
}