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

	Matrix4f Light::getShadowMatrix(const Vector3f &position) const
	{
		//return Matrix4f::scale(Vector3(0.2f, 0.2f, -0.2f)) * Matrix4f::rotationX(45) * Matrix4f::rotationY(45);
		//return  Matrix4f::fromForward(m_DiRectangleion, Vector3(0,1,0)) * Matrix4f::scale(Vector3(0.1f, 0.1f, -0.5f)); // TODO some shadow range calculations or something
		return Matrix4f::orthographic(-10, 10, -10, 10, 10, -10) * Matrix4f::lookAt(-m_DiRectangleion + position, position);
	}
}
