#include "PointCloudEntity.h"

#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "graphics/Graphics.h"

#include "engine/Engine.h"
#include "engine/Time.h"
#include "engine/Input.h"

#include "math/Vector4.h"

#include "math/Delaunay3.h"
#include "math/Triangle3.h"

#include "math/Curve.h"
#include "math/math.h"

#include "logger/log.h"

#include "resources/ResourceManager.h"

#include "engine/Keycodes.h"

namespace ftec {

	static void drawTriangle(const Triangle3f &tr, const Color32 &c)
	{
		Graphics::enqueueLine(tr.edgeab(), c);
		Graphics::enqueueLine(tr.edgebc(), c);
		Graphics::enqueueLine(tr.edgeca(), c);
	}
	static void drawTetrahedron(const Tetrahedronf &in)
	{
		Tetrahedronf t = in;

		drawTriangle(
			t.triangleabc(),
			Color32::red()
		);
		drawTriangle(
			t.triangleacd(),
			Color32::green()
		);
		drawTriangle(
			t.triangleadb(),
			Color32::cyan()
		);
		drawTriangle(
			t.trianglebdc(),
			Color32::yellow()
		);
	}


	PointCloudEntity::PointCloudEntity(std::shared_ptr<EngineContext> context, std::vector<Vector3d> vertices) : Entity(context), m_Points(std::move(vertices))
	{
		if (m_Points.size() == 0)
			return;

		del.triangulate(m_Points);

		m_Render = true;

		m_Time = -1;

		m_DiRectangleion = Vector3f(del.getBoundingBox().center());

		speed = (float)(rand() % 16);

		m_Mesh = std::make_unique<Mesh>();

		center = del.m_Center;

		for (int i = 0; i < del.getHullTriangleCount(); i++) {
			const TriangleRef &tr = del.getHullTriangleRef(i);

			Triangle3f t(del.getPoint(tr.a), del.getPoint(tr.b), del.getPoint(tr.c));

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

			m_Mesh->m_Uvs.push_back(Vector2f());
			m_Mesh->m_Uvs.push_back(Vector2f());
			m_Mesh->m_Uvs.push_back(Vector2f());

			m_Mesh->m_Triangles.push_back(i * 3 + 0);
			m_Mesh->m_Triangles.push_back(i * 3 + 1);
			m_Mesh->m_Triangles.push_back(i * 3 + 2);
		}

		m_Mesh->upload();

		m_Material = std::make_shared<PBRMaterial>(
			context->getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE),
			context->getResourceManager().load<Shader>("shaders/default")
			);
		
		m_Material->m_NormalMap = context->getResourceManager().load<Texture>(DEFAULT_TEXTURE_NORMAL);
		m_Material->m_RoughnessMap = context->getResourceManager().load<Texture>(DEFAULT_TEXTURE_BLACK);
		m_Material->m_MetallicMap = context->getResourceManager().load<Texture>(DEFAULT_TEXTURE_BLACK);
	}

	void PointCloudEntity::update()
	{// || Input::isKeyTyped(KEY_R) || Input::isKeyTyped(KEY_E) || 

		const Input &input = m_Context->getInput();

		if ((input.isKeyPressed(KEY_SPACE) || input.isKeyReleased(KEY_ENTER)) && m_Time != -1) {
			m_Render = false;
		}

		if (input.isKeyDown(KEY_N)) {
			m_Time += m_Context->getTime().deltaTime * 4;
		}
		else {
			m_Time -= m_Context->getTime().deltaTime * 4;
		}

		if (input.isKeyPressed(KEY_UP)) {
			away += 0.25f;
		}if(input.isKeyPressed(KEY_DOWN)) {
			away -= 0.25f;
		}

		m_Time = clamp(0.f, 1.f, m_Time);

		amount = tween(0.f, away, m_Time, curves::CubicBezier());

		m_Position = m_DiRectangleion * amount;

		if (m_Time < EPSILON * 4)
			m_Position = Vector3f(0, 0, 0);
	}

	void PointCloudEntity::render()
	{
		if (m_Render) {
			Matrix4f model = Matrix4f::translation(this->m_Position + center);

			Matrix4f rotation = Matrix4f::translation(-center);// Matrix4f::rotationY(amount * 37) * Matrix4f::rotationX(amount * 27) * Matrix4f::translation(-center);

			if (m_Context->getInput().isKeyDown(KEY_T)) {

				model =  Matrix4f::translation(this->m_Position + center);
				
				Graphics::enqueuePoint(model * rotation * center, Color32::red());

				for (auto &v : m_Points){
					Graphics::enqueuePoint(model * rotation * v, Color32::white());
				}

				Graphics::enqueueLine(Line3f(
					del.getBoundingBox().min, del.getBoundingBox().max
				).transform(model * rotation), Color32::green());
			}
			
			else {
				Graphics::enqueueMesh(m_Mesh.get(), m_Material.get(), model * rotation);// * 
			}
		}
	}
}
