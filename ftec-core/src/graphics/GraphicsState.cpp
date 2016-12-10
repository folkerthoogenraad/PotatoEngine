#include "GraphicsState.h"

#include <string>
#include <sstream>

#include "Shader.h"
#include "Cubemap.h"
#include "Texture.h"
#include "logger/log.h"

namespace ftec {

	std::shared_ptr<Cubemap> GraphicsState::m_Skybox = nullptr;

	Matrix4f GraphicsState::matrixModel;
	Matrix4f GraphicsState::matrixView;
	Matrix4f GraphicsState::matrixProjection;
	Vector3f GraphicsState::eyePosition;

	const Material *GraphicsState::m_Material(nullptr);

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