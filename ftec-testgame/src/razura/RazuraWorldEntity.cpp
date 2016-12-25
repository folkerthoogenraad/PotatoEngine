#include "RazuraWorldEntity.h"

#include "engine/Engine.h"
#include "engine/KeyCodes.h"
#include "engine/Input.h"

#include "resources/ResourceManager.h"

#include "math/Matrix4.h"
#include "math/Vector3.h"
#include "math/Vector2.h"

#include "graphics/Material.h"
#include "graphics/Graphics.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"

#include "logger/log.h"


namespace ftec {
	RazuraWorldEntity::RazuraWorldEntity()
	{
	}
	RazuraWorldEntity::~RazuraWorldEntity()
	{
	}
	void RazuraWorldEntity::onStart()
	{
		m_Material = std::make_unique<UnlitMaterial>();

		m_Material->m_Shader = Engine::getResourceManager().load<Shader>("shaders/mandelbrot");

		m_Material->m_TextureMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);

		m_Mesh = std::make_unique<Mesh>();
		m_Mesh->m_Vertices = {
			Vector3f(0,0,0),
			Vector3f(1,0,0),
			Vector3f(1,0,1),
			Vector3f(0,0,1)
		};
		m_Mesh->m_Uvs = {
			Vector2f(0,0),
			Vector2f(1,0),
			Vector2f(1,1),
			Vector2f(0,1)
		};
		m_Mesh->m_Triangles = {
			0,2,1,
			0,3,2
		};

		m_Mesh->recalculateNormals();
		m_Mesh->recalculateTangents();
		m_Mesh->upload();
	}

	void RazuraWorldEntity::onEnd()
	{
		m_Mesh.reset();
		m_Material.reset();
	}


	void RazuraWorldEntity::update()
	{
		
	}

	void RazuraWorldEntity::render()
	{
		Graphics::enqueueMesh(
			m_Mesh.get(),
			m_Material.get(),
			Matrix4f::identity()
		);
	}

}
