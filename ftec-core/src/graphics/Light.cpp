#include "Light.h"

namespace ftec {
	void Light::setShadowsEnabled(bool enabled)
	{
		//If its already in the wanted state, ignore everything
		if (m_ShadowsEnabled == enabled)
			return;

		m_ShadowsEnabled = enabled;

		if (m_ShadowsEnabled) {
			m_ShadowMap = std::make_shared<RenderBuffer>(SHADOW_RESOLUTION, SHADOW_RESOLUTION);
		}
		else {
			m_ShadowMap = nullptr;
		}
	}

	mat4f Light::getShadowMatrix(const vec3f &position) const
	{
		//return mat4f::scale(vec3(0.2f, 0.2f, -0.2f)) * mat4f::rotationX(45) * mat4f::rotationY(45);
		//return  mat4f::fromForward(m_Direction, vec3(0,1,0)) * mat4f::scale(vec3(0.1f, 0.1f, -0.5f)); // TODO some shadow range calculations or something
		return mat4f::orthographic(-10, 10, -10, 10, 10, -10) * mat4f::lookAt(-m_Direction + position, position);
	}
}
