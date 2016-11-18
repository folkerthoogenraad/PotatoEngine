#include "Voronoi3DEntity.h"'

#include "graphics/Graphics.h"
#include "engine/Input.h"
#include "engine/Time.h"

#include "math/helpers.h"

#include "math/tetrahedron.h"
#include "math/Delaunay3D.h"

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
			t.triangledbc(),
			color32::green()
		);
		Graphics::enqueueTriangle(
			t.triangleabd(),
			color32::cyan()
		);
		Graphics::enqueueTriangle(
			t.triangleacd(),
			color32::yellow()
		);
	}

	//TODO make these not static and stuff, whatever

	static Delaunay3D del;

	void Voronoi3DEntity::create()
	{
		m_Points.clear();

		for (int i = 0; i < 10; i++) {
			vec3f a = vec3f(
				randf(-1, 1),
				randf(-1, 1),
				randf(-1, 1)
			);

			m_Points.push_back(a);
		}

		del.triangulate(m_Points);

	}

	Voronoi3DEntity::Voronoi3DEntity()
	{
		
	}

	void Voronoi3DEntity::update()
	{
		if (Input::isKeyTyped(GLFW_KEY_SPACE)) {
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

		for (auto &p : m_Points) {
			Graphics::enqueuePoint(p, color32::red());
		}

		for (int i = 0; i < del.getTetraHedronCount(); ++i) {
			Delaunay3D::TetrahedronRef tetrahedronRef = del.getTetraHedronRef(i);
			tetrahedronf tetrahedron(
				del.getPoint(tetrahedronRef.a),
				del.getPoint(tetrahedronRef.b),
				del.getPoint(tetrahedronRef.c),
				del.getPoint(tetrahedronRef.d)
			);

			drawTetrahedron(tetrahedron);
		}


	}
}
