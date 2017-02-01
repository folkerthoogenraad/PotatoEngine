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

	static std::unique_ptr<BSP3> createFromMesh(const std::string &file)
	{
		auto bsp = std::make_unique<BSP3>();

		auto mesh = Engine::getResourceManager().load<Mesh>(file);

		BSPFace face;

		double start = Time::currentTimeMilliseconds();
		int triangleCount = 0;

		LOG("Done loading mesh, building BSP");

		for (int i = 0; i < mesh->m_Triangles.size(); i += 3) {
			triangleCount++;
			auto a = toRational(mesh->m_Vertices[i], 10000);
			auto b = toRational(mesh->m_Vertices[i + 1], 10000);
			auto c = toRational(mesh->m_Vertices[i + 2], 10000);

			face.m_ID = 0;
			face.m_DebugTag = "MeshNode";
			face.m_Vertices.clear();

			face.m_Vertices.push_back(a);
			face.m_Vertices.push_back(b);
			face.m_Vertices.push_back(c);

			face.m_Plane = Planer(a, b, c);

			bsp->insert(face, "MeshNode");
		}

		double end = Time::currentTimeMilliseconds();

		LOG("Done building bsp, starting making spaces. It took " << (end - start) << "ms for " << triangleCount << " triangles.");
		
		return std::move(bsp);
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

	void BSPEntity::onStart()
	{
		auto thing = createHarryPotterThing(m_Scene);
		//auto sphere = makeSphere(Vector3r(0, 3, 0), Vector3r(2, 2, 2));
		auto sphere = makeSphere(Vector3r(0, 0, 0), Vector3r(1, 1, 1) * 16 / 9);
		auto sphereHole = makeCylinder(Vector3r(0, 0, 0), Vector3r(1, 6, 1) / 2);
		
		thing->csgDifference(*sphere);
		//thing->csgDifference(*sphereHole);

		//addPortals(m_Scene, *sphere, sphere->getRoot());
		//addPortals(m_Scene, *sphere, sphere->getRoot());

		addPortals(m_Scene, *thing, thing->getRoot());
		//addPortals(m_Scene, *sphere, sphere->getRoot());
	}

	void BSPEntity::render()
	{

	}
}
