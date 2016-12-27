#include "RazuraPlayer.h"

#include "graphics/Mesh.h"
#include "graphics/MeshBuilder.h"
#include "graphics/Material.h"
#include "graphics/Shader.h"

#include "engine/Time.h"
#include "engine/Input.h"
#include "engine/Keycodes.h"

#include "graphics/Graphics.h"
#include "math/Matrix4.h"

#include "engine/Engine.h"
#include "resources/ResourceManager.h"

namespace ftec {
	RazuraPlayer::RazuraPlayer()
		: m_Position(0,0.5f,0)
	{
	}
	RazuraPlayer::~RazuraPlayer()
	{
	}
	void RazuraPlayer::onStart()
	{
		m_Mesh = std::make_unique<Mesh>();

		MeshBuilder::addQuad(*m_Mesh, Matrix4f::identity());
		MeshBuilder::apply(*m_Mesh);

		m_Mesh->recalculateNormals();
		m_Mesh->recalculateTangents();
		m_Mesh->upload();

		m_Material = std::make_unique<PBRMaterial>();
		m_Material->m_Shader = Engine::getResourceManager().load<Shader>("shaders/default");

		m_Material->m_TextureMap = Engine::getResourceManager().load<Texture>("textures/mario.png");
		m_Material->m_NormalMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_NORMAL);
		m_Material->m_RoughnessMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
		m_Material->m_MetallicMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_BLACK);
	}

	void RazuraPlayer::onEnd()
	{
	}

	void RazuraPlayer::update()
	{
		Vector3f motion(0, 0, 0);

		if (Input::isKeyDown(KEY_W)) {
			motion.z += 1;
		}if (Input::isKeyDown(KEY_S)) {
			motion.z -= 1;
		}if (Input::isKeyDown(KEY_A)) {
			motion.x -= 1;
		}if (Input::isKeyDown(KEY_D)) {
			motion.x += 1;
		}

		if (motion.sqrmagnitude() > 0) {
			motion.normalize();
			m_Position += motion * 2 * Time::deltaTime;
		}
	}

	void RazuraPlayer::render()
	{
		Graphics::enqueueMesh(
			m_Mesh.get(),
			m_Material.get(),
			Matrix4f::translation(m_Position)
		);
	}

}
