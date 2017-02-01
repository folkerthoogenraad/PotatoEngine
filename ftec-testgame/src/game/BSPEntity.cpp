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

#if 0
	std::unique_ptr<BSP3> createHarryPotterThing(Scene *scene)
	{
		double start = Time::currentTimeMilliseconds();

		auto box = makeBox(Vector3r(0, 0, 0), Vector3r(1, 2, 1));

		auto cylinder = makeCylinder(Vector3r(0, 2, 0), Vector3r(1, 1, 1) * 3 / 4);

		auto sphere1 = makeSphere(Vector3r(1, 0, 1), Vector3r(1, 2, 1) * 2 / 3);
		auto sphere2 = makeSphere(Vector3r(-1, 0, 1), Vector3r(1, 2, 1) * 2 / 3);
		auto sphere3 = makeSphere(Vector3r(-1, 0, -1), Vector3r(1, 2, 1) * 2 / 3);
		auto sphere4 = makeSphere(Vector3r(1, 0, -1), Vector3r(1, 2, 1) * 2 / 3);

		//auto sphere5 = makeSphere(Vector3r(0, 2, 0), Vector3r(2, 2, 2));

		double split = Time::currentTimeMilliseconds();

		box->csgDifference(*sphere1);
		box->csgDifference(*sphere2);
		box->csgDifference(*sphere3);
		box->csgDifference(*sphere4);
		box->csgDifference(*cylinder);

		box->print();

		LOG("\nREST:");
		//box->csgDifference(*sphere5);

		//box->print();

		double end = Time::currentTimeMilliseconds();

		LOG("Building BSP took " << (end - start) << "ms. CSG time was " << (split - start) << "ms!");

		return std::move(box);
	}
#endif 

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
#endif

		/*auto box1 = makeBox(Vector3r(0, 0, 0), Vector3r(1, 1, 1));
		auto box2 = makeBox(Vector3r(1, 1, 1), Vector3r(1, 1, 1));

		box1->csgDifference(*box2);*/

		auto box1 = makeBox(Vector3r(0, 0, 0), Vector3r(1, 1, 1));

		box1->print();

		addPortals(m_Scene, *box1, box1->getRoot());
	}

	void BSPEntity::render()
	{

	}
}
