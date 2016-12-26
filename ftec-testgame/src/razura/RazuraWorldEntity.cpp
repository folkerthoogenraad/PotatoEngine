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

#include "tiles/Tile.h"

#include "logger/log.h"


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
				if (t == Tile::VOID)
					continue;
				
				if (t == Tile::STONE || t == Tile::FLOOR) {
					float h = t == Tile::STONE ? 0 : 1;

					float i = (int)m_Mesh->m_Vertices.size();

					m_Mesh->m_Vertices.push_back(Vector3f(x, h, y));
					m_Mesh->m_Vertices.push_back(Vector3f(x + 1, h, y));
					m_Mesh->m_Vertices.push_back(Vector3f(x + 1, h, y + 1));
					m_Mesh->m_Vertices.push_back(Vector3f(x, h, y + 1));

					m_Mesh->m_Uvs.push_back(Vector2f(0, 0));
					m_Mesh->m_Uvs.push_back(Vector2f(1, 0));
					m_Mesh->m_Uvs.push_back(Vector2f(1, 1));
					m_Mesh->m_Uvs.push_back(Vector2f(0, 1));

					m_Mesh->m_Triangles.push_back(i);
					m_Mesh->m_Triangles.push_back(i + 2);
					m_Mesh->m_Triangles.push_back(i + 1);

					m_Mesh->m_Triangles.push_back(i);
					m_Mesh->m_Triangles.push_back(i + 3);
					m_Mesh->m_Triangles.push_back(i + 2);
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
