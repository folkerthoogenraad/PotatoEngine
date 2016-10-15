#include "GraphicsState.h"

#include <string>
#include <sstream>

#include "Shader.h"
#include "Cubemap.h"
#include "Texture.h"
#include "logger/log.h"

namespace ftec {

	std::shared_ptr<Cubemap> GraphicsState::m_Skybox = nullptr;

	mat4 GraphicsState::matrixModel;
	mat4 GraphicsState::matrixView;
	mat4 GraphicsState::matrixProjection;
	vec3f GraphicsState::eyePosition;

	std::shared_ptr<Material> GraphicsState::m_Material(nullptr);

	LightSlot GraphicsState::m_Lights[MAX_LIGHTS];

	void GraphicsState::prepare()
	{
		if (!m_Material) {
			LOG("Graphics state material is null");
			return;
		}

		m_Material->prepare();
	}

}