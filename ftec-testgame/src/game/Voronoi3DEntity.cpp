#include "Voronoi3DEntity.h"

#include "graphics/Graphics.h"
#include "engine/Input.h"
#include "engine/Engine.h"
#include "engine/Time.h"

#include "scene/Scene.h"

#include "math/math.h"
#include "math/mat4.h"

#include "math/tetrahedron.h"
#include "math/Delaunay3.h"
#include "math/Voronoi3.h"
#include "logger/log.h"

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "PointCloudEntity.h"

#include <set>

namespace ftec {

	static float randf(float min, float max) 
	{
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		return r * (max - min) + min;
	}

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
			t.triangleabc(), color32::white()
		);
		drawTriangle(
			t.triangleacd(), color32::white()
		);
		drawTriangle(
			t.triangleadb(), color32::white()
		);
		drawTriangle(
			t.trianglebdc(), color32::white()
		);
	}


	//TODO make these not static and stuff, whatever
	static Voronoi3d voronoi;
	static Delaunay3d delaunay;

	void Voronoi3DEntity::create()
	{
		delaunay.triangulate(m_Points);
		voronoi.create(delaunay);

		for (const auto &l : voronoi.getLegos()) {
			Engine::getScene()->addEntity(std::make_shared<PointCloudEntity>(l.m_Vertices));
		}
		//Engine::getScene()->addEntity(std::make_shared<PointCloudEntity>(m_Points));
	}

	Voronoi3DEntity::Voronoi3DEntity()
	{
		
	}

	void Voronoi3DEntity::update()
	{
		if (Input::isKeyTyped(GLFW_KEY_ENTER)) {
			/*m_Points = {
				vec3d(-0.729189, -0.220405, 0.647628),
				vec3d(-0.792915, 0.0644285, 0.190272),
				vec3d(-0.579266, -0.558579, 1.01144),
				vec3d(-0.198262, -0.528971, 0.0285342),
				vec3d(-0.0333755, -0.98818, 0.615922),
				vec3d(-0.264774, -0.418219, -0.0485973),
				vec3d(-0.197283, -0.98818, 1.01144),
				vec3d(-0.730016, -0.218901, 0.646062),
				vec3d(-0.884902, 0.132082, 0.214651),
				vec3d(-0.700895, -0.526021, 1.01144),
				vec3d(-1.04433, 0.160198, 0.163342),
				vec3d(-1.04433, -0.559212, 1.01144),
				vec3d(-0.305183, -0.528646, -0.184989),
				vec3d(-0.802971, -0.98818, -0.919672),
				vec3d(-1.04433, -0.98818, -1.04203),
				vec3d(-1.04433, -0.98818, 1.01144),
			};*/
			create();
		}


		if (Input::isKeyTyped(GLFW_KEY_SPACE)) {
			static int a = 0;

			mat4f mat = mat4f::rotationY(34.18413248f) * mat4f::rotationX(75.05415421f);

			double size = 2.0;

			m_Points.clear();
			std::set<vec3d> vecs;

			/*for (int x = 0; x < size; x++) {
				for (int y = 0; y < size; y++) {
					for (int z = 0; z < size; z++) {
						vec3d a = vec3d(
							x / size - 0.5,
							y / size - 0.5,
							z / size - 0.5
						);
						m_Points.push_back(mat * a);
					}
				}
			}*/
			
			for (int i = 0; i < 5; i++) {
				vec3d a = vec3d(
					randf(-1,1), randf(-2, 2), randf(-1, 1)
				);

				vecs.insert(a);
			}

			++a;

			for (auto &v : vecs) {
				m_Points.push_back(v);
			}

			create();
		}

		if (true)
			return;

		if (Input::isKeyTyped(GLFW_KEY_R)) {
			static int r = 0;

			r %= 5;

			m_Points.clear();

			auto t = tetrahedrond::unitTetrahedron();

			m_Points.push_back(t.a);

			if(r >= 1)
				m_Points.push_back(t.b);
			if (r >= 2)
				m_Points.push_back(t.c);
			if (r >= 3)
				m_Points.push_back(t.d);
			if (r >= 4)
				m_Points.push_back(vec3d(0,0));

			r++;

			create();
		}

		if (Input::isKeyTyped(GLFW_KEY_E)) {
			m_Points.clear();

			mat4f mat = mat4f::identity();// mat4f::rotationY(30) * mat4f::scale(vec3f(1.f, 1.f, 2.0f));

			for (int x = -1; x < 2; x+= 2) {
				for (int y = -1; y < 2; y += 2) {
					for (int z = -1; z < 2; z += 2) {
						vec3f a = vec3f(
							(float) x, (float) y, (float) z
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
		//Draw the grid
		/*for (int i = 0; i < 11; i++) {
			Graphics::enqueueLine(
				line3f(vec3f(i - 5, 0, -5), vec3f(i - 5, 0, 5)),
				color32::dkgray()
			);
			Graphics::enqueueLine(
				line3f(vec3f(-5, 0, i-5), vec3f(5, 0, i - 5)),
				color32::dkgray()
			);
		}*/

		/*for (int i = 0; i < delaunay.getTetraHedronCount(); i++) {
			TetrahedronRef ref = delaunay.getTetraHedronRef(i);

			tetrahedronf tetra(
				delaunay.getPoint(ref.a),
				delaunay.getPoint(ref.b),
				delaunay.getPoint(ref.c),
				delaunay.getPoint(ref.d)
			);

			drawTetrahedron(tetra);
		}*/

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
