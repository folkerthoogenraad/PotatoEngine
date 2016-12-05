#include "PointCloudEntity.h"

#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "graphics/Graphics.h"

#include "engine/Engine.h"
#include "engine/Time.h"
#include "engine/Input.h"

#include "math/Delaunay3.h"
#include "math/triangle3.h"

#include "math/Curve.h"
#include "math/math.h"

#include "logger/log.h"

namespace ftec {

	static void drawTriangle(const triangle3f &tr, const color32 &c)
	{
		Graphics::enqueueLine(tr.edgeab(), c);
		Graphics::enqueueLine(tr.edgebc(), c);
		Graphics::enqueueLine(tr.edgeca(), c);
	}
	static void drawTetrahedron(const tetrahedronf &in)
	{
		tetrahedronf t = in;

		drawTriangle(
			t.triangleabc(),
			color32::red()
		);
		drawTriangle(
			t.triangleacd(),
			color32::green()
		);
		drawTriangle(
			t.triangleadb(),
			color32::cyan()
		);
		drawTriangle(
			t.trianglebdc(),
			color32::yellow()
		);
	}


	PointCloudEntity::PointCloudEntity(std::vector<vec3d> vertices) : m_Points(std::move(vertices))
	{
		if (m_Points.size() == 0)
			return;

		del.triangulate(m_Points);

		m_Render = true;

		m_Time = -1;

		m_Direction = vec3f(del.getBoundingBox().center());

		speed = (rand() % 16);

		m_Mesh = std::make_unique<Mesh>();

		center = del.m_Center;

		for (int i = 0; i < del.getHullTriangleCount(); i++) {
			const TriangleRef &tr = del.getHullTriangleRef(i);

			triangle3f t(del.getPoint(tr.a), del.getPoint(tr.b), del.getPoint(tr.c));

			if (t.distanceFrom(center) > 0)
				t.flip();

			m_Mesh->m_Vertices.push_back(t.a);
			m_Mesh->m_Vertices.push_back(t.b);
			m_Mesh->m_Vertices.push_back(t.c);

			vec3f normal = vec3f(t.normal().normalize());
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
	}

	void PointCloudEntity::update()
	{// || Input::isKeyTyped(GLFW_KEY_R) || Input::isKeyTyped(GLFW_KEY_E) || 
		if ((Input::isKeyTyped(GLFW_KEY_SPACE) || Input::isKeyTyped(GLFW_KEY_ENTER)) && m_Time != -1) {
			m_Render = false;
		}

		if (Input::isKeyDown(GLFW_KEY_N)) {
			m_Time += Time::deltaTime * 4;
		}
		else {
			m_Time -= Time::deltaTime * 4;
		}

		if (Input::isKeyTyped(GLFW_KEY_UP)) {
			away += 0.25f;
		}if(Input::isKeyTyped(GLFW_KEY_DOWN)) {
			away -= 0.25f;
		}

		m_Time = clamp(0.f, 1.f, m_Time);

		amount = tween(0.f, away, m_Time, curves::CubicBezier());

		m_Position = m_Direction * amount;

		if (m_Time < EPSILON * 4)
			m_Position = vec3f(0, 0, 0);
	}

	void PointCloudEntity::render()
	{
		if (m_Render) {
			mat4f model = mat4f::translation(this->m_Position + center);

			mat4f rotation = mat4f::translation(-center);// mat4f::rotationY(amount * 37) * mat4f::rotationX(amount * 27) * mat4f::translation(-center);

			if (Input::isKeyDown(GLFW_KEY_T)){

				model =  mat4f::translation(this->m_Position + center);
				
				Graphics::enqueuePoint(model * rotation * center, color32::red());

				for (auto &v : m_Points){
					Graphics::enqueuePoint(model * rotation * v);
				}

				Graphics::enqueueLine(line3f(
					del.getBoundingBox().min, del.getBoundingBox().max
				).transform(model * rotation), color32::green());
			}
			
			else {
				Graphics::enqueueMesh(m_Mesh.get(), m_Material, model * rotation);// * 
			}
		}
	}
}
