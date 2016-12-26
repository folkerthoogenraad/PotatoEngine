#include "RazuraPlayer.h"

#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Shader.h"

#include "graphics/Graphics.h"
#include "math/Matrix4.h"

#include "engine/Engine.h"
#include "resources/ResourceManager.h"

namespace ftec {
	RazuraPlayer::RazuraPlayer()
	{
	}
	RazuraPlayer::~RazuraPlayer()
	{
	}
	void RazuraPlayer::onStart()
	{
		m_Mesh = Engine::getResourceManager().load<Mesh>("mesh/mushroom.obj");

		m_Material = std::make_unique<PBRMaterial>();
		m_Material->m_Shader = Engine::getResourceManager().load<Shader>("shaders/default");

		m_Material->m_TextureMap = Engine::getResourceManager().load<Texture>("textures/mushroom.png");
		m_Material->m_NormalMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_NORMAL);
		m_Material->m_RoughnessMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
		m_Material->m_MetallicMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_BLACK);
	}

	void RazuraPlayer::onEnd()
	{
	}

	void RazuraPlayer::update()
	{
	}

	void RazuraPlayer::render()
	{
		Graphics::enqueueMesh(
			m_Mesh.get(),
			m_Material.get(),
			Matrix4f::identity()
		);
	}

}
