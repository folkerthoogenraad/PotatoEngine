#include "Voronoi3DEntity.h"

#include "graphics/Graphics.h"
#include "engine/Input.h"
#include "engine/Engine.h"
#include "engine/Time.h"

#include "scene/Scene.h"

#include "math/helpers.h"

#include "math/tetrahedron.h"
#include "math/Delaunay3D.h"
#include "math/Voronoi3D.h"
#include "logger/log.h"

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "PointCloudEntity.h"

namespace ftec {

	static float randf(float min, float max) 
	{
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		return r * (max - min) + min;
	}

	static void drawTetrahedron(const tetrahedronf &in)
	{
		tetrahedronf t = in;

		Graphics::enqueueTriangle(
			t.triangleabc(),
			color32::red()
		);
		Graphics::enqueueTriangle(
			t.triangleacd(),
			color32::green()
		);
		Graphics::enqueueTriangle(
			t.triangleadb(),
			color32::cyan()
		);
		Graphics::enqueueTriangle(
			t.trianglebdc(),
			color32::yellow()
		);
	}

	//TODO make these not static and stuff, whatever
	static Voronoi3D voronoi;

	void Voronoi3DEntity::create()
	{
		Delaunay3D delaunay;

		delaunay.triangulate(m_Points);
		voronoi.create(delaunay);

		for (const auto &l : voronoi.getLegos()) {
			Engine::getScene()->addEntity(std::make_shared<PointCloudEntity>(l));
		}

	}

	Voronoi3DEntity::Voronoi3DEntity()
	{
		
	}

	void Voronoi3DEntity::update()
	{
		if (Input::isKeyTyped(GLFW_KEY_ENTER)) {
			create();
		}


		if (Input::isKeyTyped(GLFW_KEY_SPACE)) {
			m_Points.clear();

			for (int i = 0; i < 10; i++) {
				vec3f a = vec3f(
					randf(-1, 1),
					randf(-1, 1),
					randf(-1, 1)
				);

				m_Points.push_back(a);
			}


			create();
		}

		if (Input::isKeyTyped(GLFW_KEY_R)) {
			static int r = 0;

			r %= 5;

			m_Points.clear();

			auto t = tetrahedronf::unitTetrahedron();

			m_Points.push_back(t.a);

			if(r >= 1)
				m_Points.push_back(t.b);
			if (r >= 2)
				m_Points.push_back(t.c);
			if (r >= 3)
				m_Points.push_back(t.d);
			if (r >= 4)
				m_Points.push_back(vec3f(0,0));

			r++;

			create();
		}

		if (Input::isKeyTyped(GLFW_KEY_E)) {
			m_Points.clear();

			mat4 mat = mat4::identity();// mat4::rotationY(30) * mat4::scale(vec3f(1.f, 1.f, 2.0f));

			for (int x = -1; x < 2; x+= 2) {
				for (int y = -1; y < 2; y += 2) {
					for (int z = -1; z < 2; z += 2) {
						vec3f a = vec3f(
							x, y, z
						);

						m_Points.push_back(mat * a);
					}
				}
				
			}

			create();
		}
	
	}


	void Voronoi3DEntity::render()
	{
		for (int i = 0; i < 11; i++) {
			Graphics::enqueueLine(
				line3f(vec3f(i - 5, 0, -5), vec3f(i - 5, 0, 5)),
				color32::dkgray()
			);
			Graphics::enqueueLine(
				line3f(vec3f(-5, 0, i-5), vec3f(5, 0, i - 5)),
				color32::dkgray()
			);
		}

		/*for (auto &l : voronoi.getLegos()) {
			for (auto &v : l.m_Vertices) {
				Graphics::enqueuePoint(v, color32::green());
			}
		}

		for (int i = 0; i < voronoi.getDelaunay().getPointCount(); i++) {
			glPointSize(5.f);
			Graphics::enqueuePoint(voronoi.getDelaunay().getPoint(i), color32::red());
		}

		for (auto &p : m_Points) {
			Graphics::enqueuePoint(p, color32::red());
		}

		for (int i = 0; i < del.getHullTriangleCount(); ++i) {
			TriangleRef ref = del.getHullTriangleRef(i);

			Graphics::enqueueTriangle(triangle3f(del.getPoint(ref.a), del.getPoint(ref.b), del.getPoint(ref.c)));
		}*/


	}
}
