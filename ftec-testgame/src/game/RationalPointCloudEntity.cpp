#include "RationalPointCloudEntity.h"

#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "graphics/Graphics.h"

#include "engine/Engine.h"
#include "resources/ResourceManager.h"

namespace ftec {

	RationalPointCloudEntity::RationalPointCloudEntity(const std::vector<Vector3r>& vertices)
	{
		del.triangulate(vertices);

		m_Mesh = std::make_unique<Mesh>();

		auto toFloat = [](const Vector3r &v) -> Vector3f {
			Vector3f out;
			out.x = v.x.convert_to<float>();
			out.y = v.y.convert_to<float>();
			out.z = v.z.convert_to<float>();
			return out;
		};

		Vector3r center = toFloat(del.m_Center);

		for (int i = 0; i < del.getHullTriangleCount(); i++) {
			const TriangleRef &tr = del.getHullTriangleRef(i);

			Triangle3f t(toFloat(del.getPoint(tr.a)), toFloat(del.getPoint(tr.b)), toFloat(del.getPoint(tr.c)));

			if (t.distanceFrom(center) > 0)
				t.flip();

			m_Mesh->m_Vertices.push_back(t.a);
			m_Mesh->m_Vertices.push_back(t.b);
			m_Mesh->m_Vertices.push_back(t.c);

			Vector3f normal = Vector3f(t.normal().normalize());
			Vector3f tangent = Vector3f::cross(normal, Vector3f(0, 1, 0));

			if (tangent.magnitude() == 0)
				tangent = Vector3f::cross(normal, Vector3f(1, 0, 0));

			m_Mesh->m_Normals.push_back(normal);
			m_Mesh->m_Normals.push_back(normal);
			m_Mesh->m_Normals.push_back(normal);

			m_Mesh->m_Tangents.push_back(tangent);
			m_Mesh->m_Tangents.push_back(tangent);
			m_Mesh->m_Tangents.push_back(tangent);

			if (abs(Vector3f::dot(normal, Vector3f(0, 1, 0))) > 0.8f) {
				m_Mesh->m_Uvs.push_back(Vector2f(t.a.x, t.a.z));
				m_Mesh->m_Uvs.push_back(Vector2f(t.b.x, t.b.z));
				m_Mesh->m_Uvs.push_back(Vector2f(t.c.x, t.c.z));
			}
			else {
				m_Mesh->m_Uvs.push_back(Vector2f(t.a.x + t.a.z, t.a.y));
				m_Mesh->m_Uvs.push_back(Vector2f(t.b.x + t.b.z, t.b.y));
				m_Mesh->m_Uvs.push_back(Vector2f(t.c.x + t.c.z, t.c.y));
			}

			m_Mesh->m_Triangles.push_back(i * 3 + 0);
			m_Mesh->m_Triangles.push_back(i * 3 + 1);
			m_Mesh->m_Triangles.push_back(i * 3 + 2);
		}

		m_Mesh->upload();

		m_Material = std::make_shared<PBRMaterial>(
			Engine::getResourceManager().load<Texture>("textures/concrete.jpg"),
			Engine::getResourceManager().load<Shader>("shaders/default")
			);

		m_Material->m_NormalMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_NORMAL);
		m_Material->m_RoughnessMap = Engine::getResourceManager().load<Texture>("textures/concrete.jpg");
		m_Material->m_MetallicMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_BLACK);

	}

	void RationalPointCloudEntity::render()
	{
		Graphics::enqueueMesh(m_Mesh.get(), m_Material.get(), Matrix4f::identity());
	}
}

