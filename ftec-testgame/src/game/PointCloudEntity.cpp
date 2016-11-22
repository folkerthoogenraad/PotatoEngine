#include "PointCloudEntity.h"
#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "engine/Engine.h"

#include "math/Delaunay3D.h"
#include "math/triangle3.h"

namespace ftec {

	PointCloudEntity::PointCloudEntity(std::vector<vec3f> points) : m_Points(std::move(points))
	{
		Delaunay3D del;

		del.triangulate(m_Points);

		m_Mesh = std::make_unique<Mesh>();
		vec3f center = del.getBoundingBox().center();

		for (int i = 0; i < del.getHullTriangleCount(); i++) {
			const TriangleRef &tr = del.getHullTriangleRef(i);

			triangle3f t(del.getPoint(tr.a), del.getPoint(tr.b), del.getPoint(tr.c));

			if (t.distanceFrom(center) > 0)
				t.flip();

			m_Mesh->m_Vertices.push_back(t.a);
			m_Mesh->m_Vertices.push_back(t.b);
			m_Mesh->m_Vertices.push_back(t.c);

			vec3f normal = t.normal().normalize();
			vec3f tangent = vec3f::cross(normal, vec3f(0, 1, 0));

			if (tangent.magnitude() == 0)
				tangent = vec3f::cross(normal, vec3f(1, 0, 0));

			m_Mesh->m_Normals.push_back(normal);
			m_Mesh->m_Normals.push_back(normal);
			m_Mesh->m_Normals.push_back(normal);

			m_Mesh->m_Tangents.push_back(tangent);
			m_Mesh->m_Tangents.push_back(tangent);
			m_Mesh->m_Tangents.push_back(tangent);

			m_Mesh->m_Uvs.push_back(vec2f());
			m_Mesh->m_Uvs.push_back(vec2f());
			m_Mesh->m_Uvs.push_back(vec2f());

			m_Mesh->m_Triangles.push_back({ i * 3 + 0, i * 3 + 0, i * 3 + 0 });
			m_Mesh->m_Triangles.push_back({ i * 3 + 1, i * 3 + 1, i * 3 + 1 });
			m_Mesh->m_Triangles.push_back({ i * 3 + 2, i * 3 + 2, i * 3 + 2 });
		}

		m_Mesh->upload();

		m_Material = std::make_shared<PBRMaterial>(
			Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE),
			Engine::getResourceManager().load<Shader>("shaders/default")
			);
		m_Material->m_Metallicness = 0.2f;
		m_Material->m_Roughness = 0.2f;

		m_Material->m_NormalMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_NORMAL);
		m_Material->m_RoughnessMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
		m_Material->m_MetallicMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);

		m_Time = 0;
	}

	void PointCloudEntity::update()
	{
		if ((Input::isKeyPressed(GLFW_KEY_SPACE) || Input::isKeyPressed(GLFW_KEY_R)) && m_Time != 0) {
			m_Render = false;
		}
		m_Time += Time::deltaTime;

		m_Position = vec3f(
			(float)sin(m_Time * 1.8) * 1.1f * 3,
			(float)cos(m_Time * 1.1) * 1.8f * 3,
			(float)sin(m_Time * 1.4) * 1.4f * 3
		);

	}

	void PointCloudEntity::render()
	{
		if (m_Render) {
			Graphics::enqueueMesh(m_Mesh.get(), m_Material);// , mat4::translation(this->m_Position) * mat4::rotationY(m_Time * 20.f));
		}
	}
}
