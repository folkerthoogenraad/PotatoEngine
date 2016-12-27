#include "RazuraWorldEntity.h"

#include "engine/Engine.h"
#include "engine/KeyCodes.h"
#include "engine/Input.h"
#include "engine/Time.h"

#include "resources/ResourceManager.h"

#include "math/Matrix4.h"
#include "math/Vector3.h"
#include "math/Vector2.h"

#include "graphics/Material.h"
#include "graphics/Graphics.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"

#include "tiles/Tile.h"

#include "logger/log.h"

#include "graphics/MeshBuilder.h"


namespace ftec {
	RazuraWorldEntity::RazuraWorldEntity()
		:m_Map(16,16)
	{
	}

	RazuraWorldEntity::~RazuraWorldEntity()
	{
	}

	void RazuraWorldEntity::onStart()
	{

		for (int x = 0; x < m_Map.getWidth(); x++) {
			for (int y = 0; y < m_Map.getHeight(); y++) {
				m_Map.setTile(x, y, (Tile) (rand() % (int)Tile::COUNT));
			}
		}

		m_Material = std::make_unique<PBRMaterial>();
		m_Material->m_Shader = Engine::getResourceManager().load<Shader>("shaders/default");

		m_Material->m_TextureMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
		m_Material->m_RoughnessMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);

		m_Material->m_MetallicMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_BLACK);
		m_Material->m_NormalMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_NORMAL);

		m_Mesh = std::make_unique<Mesh>();

		for(int x = 0; x < m_Map.getWidth(); x++){
			for (int y = 0; y < m_Map.getHeight(); y++) {
				Tile t = m_Map.getTile(x, y);
				
				if (t != Tile::VOID) {
					MeshBuilder::addQuad(
						*m_Mesh,
						Matrix4f::fromForward(Vector3f(0, 1, 0), Vector3f(0, 0, -1)) * 
						Matrix4f::translation(x + 0.5f, y + 0.5f, 0)
					);
				}
			}
		}

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
