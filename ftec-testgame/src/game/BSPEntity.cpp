#include "BSPEntity.h"
#include "RationalPointCloudEntity.h"

#include "math/Rational.h"
#include "math/Ray3.h"
#include "math/BSP3.h"
#include "math/Line3.h"
#include "math/Vector4.h"

#include "engine/Engine.h"
#include "resources/ResourceManager.h"

#include "scene/Scene.h"

#include "graphics/Graphics.h"
#include "graphics/Mesh.h"

#include "engine/Time.h"

#include "logger/log.h"

#include "graphics/GL.h"
#include "engine/Input.h"
#include "engine/Keycodes.h"

namespace ftec {

	static void addPortals(Scene *scene, BSP3 &bsp, BSPNode3* node)
	{
		int solidcount = bsp.solidcount();
		int current = 0;

		bsp.forEachCell([&](BSPNode3* node) {
			BSPCell3 cell = node->calculateCell();
			current++;

			if (cell.m_Intersections.size() > 3) {
				std::vector<Vector3<rational>> vertices;

				LOG("Creating space. (" << current << "/" << solidcount << ") \tV: " << cell.m_Intersections.size());

				//Not sure if i can even do this
				for (int i = 0; i < cell.m_Intersections.size(); i++)
				{
					vertices.push_back(std::move(cell.m_Intersections[i].vertex));
				}

				scene->addEntity(std::make_unique<RationalPointCloudEntity>(vertices));
			}
			else {
				LOG("Attempting to create mesh, but amount of vertices is too low.");
			}
		});
	}

	std::unique_ptr<BSP3> createHarryPotterThing(Scene *scene)
	{
		double start = Time::currentTimeMilliseconds();

		auto box = makeBox(Vector3r(0, 0, 0), Vector3r(1, 2, 1));

		auto cylinder = makeCylinder(Vector3r(0, 2, 0), Vector3r(1, 1, 1) * 3 / 4);

		auto sphere1 = makeSphere(Vector3r(1, 0, 1), Vector3r(1, 2, 1) * 2 / 3);
		auto sphere2 = makeSphere(Vector3r(-1, 0, 1), Vector3r(1, 2, 1) * 2 / 3);
		auto sphere3 = makeSphere(Vector3r(-1, 0, -1), Vector3r(1, 2, 1) * 2 / 3);
		auto sphere4 = makeSphere(Vector3r(1, 0, -1), Vector3r(1, 2, 1) * 2 / 3);

		box->csgDifference(*sphere1);
		box->csgDifference(*sphere2);
		box->csgDifference(*sphere3);
		box->csgDifference(*sphere4);
		box->csgDifference(*cylinder);

		box->print();

		LOG("\nREST:");
		//box->csgDifference(*sphere5);

		//box->print();


		double split = Time::currentTimeMilliseconds();
		double end = Time::currentTimeMilliseconds();

		LOG("Building BSP took " << (end - start) << "ms. CSG time was " << (split - start) << "ms!");

		return std::move(box);
	}

	std::unique_ptr<BSP3> createBug()
	{
		auto box1 = makeBox(Vector3r(0, 0, 0), Vector3r(1, 1, 1));

		rational p = rational(1);

		auto cyl1 = makeBox(Vector3r(1, 1, 1) * p, Vector3r(1, 1, 1));
		auto sphere1 = makeSphere(Vector3r(1, 1, 1) * p, Vector3r(1, 1, 1) * 2 / 3);
		auto box2 = makeBox(Vector3r(1, 1, 1) * p, Vector3r(1, 8, 1) * 1 / 3);

		//Change this order and it breaks/fixes
		cyl1->csgDifference(*sphere1);
		cyl1->csgDifference(*box2);

		box1->csgUnion(*cyl1);

		box1->print();
		
		return std::move(box1);
	}

	void BSPEntity::onStart()
	{
#if 0
		auto result = makeBox(Vector3r(0,0,0), Vector3r(4,4,4));

		auto box1 = makeBox(Vector3r(4, 0, 0), Vector3r(3, 4, 4));
		auto box2 = makeBox(Vector3r(-4, 0, 0), Vector3r(3, 4, 4));

		auto box3 = makeBox(Vector3r(0, 0, 4), Vector3r(4, 4, 3));
		auto box4 = makeBox(Vector3r(0, 0, -4), Vector3r(4, 4, 3));

		auto box5 = makeBox(Vector3r(0, 4, 0), Vector3r(4, 3, 4));
		auto box6 = makeBox(Vector3r(0, -4, 0), Vector3r(4, 3, 4));

		result->csgDifference(*box1);
		result->csgDifference(*box2);
		result->csgDifference(*box3);
		result->csgDifference(*box4);
		result->csgDifference(*box5);
		result->csgDifference(*box6);

		result->print();

		auto box7 = makeBox(Vector3r(1, 1, 1) * 0 / 7, Vector3r(1, 1, 1) * 8 / 7);

		result->csgDifference(*box7);

		addPortals(m_Scene, *result, result->getRoot());
		addPortals(m_Scene, *box7, box7->getRoot());


		double start = Time::currentTimeMilliseconds();

		auto box1 = makeBox(Vector3r(1, 1, 1) * -5 / 17 , Vector3r(1, 1, 1));

		auto box2 = makeSphere(Vector3r(1, 1, 1), Vector3r(1, 1, 1));
		
		auto box3 = makeSphere(Vector3r(1, 1, 1), Vector3r(1, 1, 1) * 2 / 3);
		auto cyl1 = makeCylinder(Vector3r(1, 1, 1), Vector3r(1, 10, 1) * 1 / 3);

		auto box4 = makeBox(Vector3r(0, 0, 0), Vector3r(12, 1, 1) * 4 / 5);

		auto sphere1 = makeSphere(Vector3r(-1, 1, -1), Vector3r(1, 1, 1));
		auto cyl2 = makeCylinder(Vector3r(-1, 1, -1), Vector3r(1, 10, 1) * 1 / 3);


		box2->csgDifference(*box3);
		box2->csgDifference(*cyl1);

		box1->csgUnion(*box2);

		//sphere1->csgDifference(*box2);
		//box1->csgDifference(*sphere1);

		//box1->csgDifference(*box4);

		double end = Time::currentTimeMilliseconds();

		LOG("CSG TIME " << (end - start) << "ms.");

		addPortals(m_Scene, *box1, box1->getRoot());
#endif

#if 0
		auto box1 = createHarryPotterThing(m_Scene);

		auto sphere = makeSphere(Vector3r(1, 0, 1), Vector3r(2, 2, 2));
		auto cyl = makeCylinder(Vector3r(1, 0, 1), Vector3r(1, 8, 1) * 1 / 2);
		
		sphere->csgDifference(*box1);
		sphere->csgDifference(*cyl);

		addPortals(m_Scene, *sphere, sphere->getRoot());
#endif
		
		auto box1 = createBug();

		addPortals(m_Scene, *box1, box1->getRoot());
	}

	void BSPEntity::render()
	{
		if (Input::isKeyDown(KEY_SPACE)) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}
