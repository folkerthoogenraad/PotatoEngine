#include "Terrain.h"

#include "graphics/Mesh.h"
#include "graphics/Graphics.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"

#include "resources/ResourceManager.h"
#include "engine/Engine.h"

#include "math/Matrix4.h"

#include "logger/log.h"

#include <assert.h>

#define SMOOTH false

namespace ftec {
	Terrain::Terrain(int width, int height, float resolution)
		: m_Width(width), m_Height(height), m_Resolution(resolution)
	{
		assert(m_Width > 0);
		assert(m_Height > 0);

		m_Data.resize(m_Width * m_Height);
		std::fill(m_Data.begin(), m_Data.end(), (const float)-1);
	}

	void Terrain::create()
	{
		if (!m_Mesh)
			m_Mesh = std::make_shared<Mesh>();

		if (SMOOTH) {
			//------------------------------------------------------------------//
			// Create vertices
			//------------------------------------------------------------------//
			m_Mesh->m_Vertices.clear();
			m_Mesh->m_Uvs.clear();

			m_Mesh->m_Vertices.reserve(m_Width * m_Height);
			m_Mesh->m_Uvs.reserve(m_Width * m_Height);

			for (int x = 0; x < m_Width; x++) {
				for (int y = 0; y < m_Height; y++) {
					m_Mesh->m_Vertices.push_back(Vector3f(x / m_Resolution, getHeightRaw(x, y), y / m_Resolution));
					m_Mesh->m_Uvs.push_back(Vector2f(x / (float)m_Width * 100, y / (float)m_Height * 100));
				}
			}

			//------------------------------------------------------------------//
			// Creating triangles
			//------------------------------------------------------------------//
			m_Mesh->m_Triangles.clear();

			for (int x = 0; x < m_Width - 1; x++) {
				for (int y = 0; y < m_Height - 1; y++) {
					int i0 = x + y * m_Width;
					int i1 = (x + 1) + y * m_Width;

					int i2 = (x + 1) + (y + 1) * m_Width;
					int i3 = x + (y + 1) * m_Width;

					m_Mesh->m_Triangles.push_back(i0);
					m_Mesh->m_Triangles.push_back(i1);
					m_Mesh->m_Triangles.push_back(i2);

					m_Mesh->m_Triangles.push_back(i0);
					m_Mesh->m_Triangles.push_back(i2);
					m_Mesh->m_Triangles.push_back(i3);
				}
			}
		}
		else {
			//------------------------------------------------------------------//
			// Create vertices
			//------------------------------------------------------------------//
			m_Mesh->m_Vertices.clear();
			m_Mesh->m_Uvs.clear();
			m_Mesh->m_Triangles.clear();

			m_Mesh->m_Vertices.reserve(m_Width * m_Height);
			m_Mesh->m_Uvs.reserve(m_Width * m_Height);

			int index = 0;

			auto add = [&](int x, int y) {
				m_Mesh->m_Vertices.push_back(Vector3f(x / m_Resolution, getHeightRaw(x, y), y / m_Resolution));
				m_Mesh->m_Uvs.push_back(Vector2f(x / (float)m_Width * 100, y / (float)m_Height * 100));
				m_Mesh->m_Triangles.push_back(index);
				index++;
			};

			for (int x = 0; x < m_Width - 1; x++) {
				for (int y = 0; y < m_Height - 1; y++) {
					add(x, y);
					add(x + 1, y + 1);
					add(x + 1, y);

					add(x, y);
					add(x, y + 1);
					add(x + 1, y + 1);
				}
			}
		}

		m_Mesh->recalculateNormals();
		m_Mesh->recalculateTangents();
		m_Mesh->upload();
	}

	void Terrain::render()
	{
		//This ofcourse is all temp stuff, dear god
		static TerrainMaterial material(
			Engine::getResourceManager().load<Shader>("shaders/terrain")
			);

		material.m_TextureMap = Engine::getResourceManager().load<Texture>("textures/terrain/grass.png");

		Graphics::enqueueMesh(
			m_Mesh.get(),
			&material,
			Matrix4f::identity()
		);
	}

	float Terrain::getHeightRaw(int x, int y)
	{
		return m_Data[x + y * m_Width];
	}

	float Terrain::getHeightEdgeloop(int x, int y)
	{
		//This can be optimized a fuckton
		//Like, 30+ fucktons

		//Also this is wrong currently. The looping with the - 1 is actually not correct.
		while (x < 0) x += m_Width - 1;
		while (x >= m_Width) x -= m_Width - 1;
		while (y < 0)  y += m_Height - 1;
		while (y >= m_Height) y -= m_Height - 1;

		float f = m_Data[x + y * m_Width];

		return f;
	}

	void Terrain::setHeightRaw(int x, int y, float value)
	{
		m_Data[x + y * m_Width] = value;
	}
}
