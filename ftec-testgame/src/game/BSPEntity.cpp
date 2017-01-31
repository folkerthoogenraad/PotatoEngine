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
		bsp.forEach([&scene](BSPNode3* node) {
			BSPCell3 cell = node->calculateCell();

			if (cell.m_Intersections.size() > 3) {
				std::vector<Vector3<rational>> vertices;

				LOG("Creating space. (" << cell.m_Intersections.size() << ")");

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

	void BSPEntity::onStart()
	{
		{
			auto box1 = makeBox(Vector3r(1, 1, 1) * 2 / 5, Vector3r(1, 1, 1));
			auto box2 = makeBox(Vector3r(1, 1, 1) * 2 / 5, Vector3r(1, 1, 1) * 2 / 3);

			auto box3 = makeBox(Vector3r(0, 0, 0), Vector3r(1, 2, 1));
			auto boxl = makeBox(Vector3r(0, 0, 0), Vector3r(1, 2, 1) * 3 / 2);
			
			//Box with gap in it!
			box1->csgDifference(*box2);
			box3->csgDifference(*box1);

			auto box4 = makeBox(Vector3r(0, 0, 0), Vector3r(6, 1, 1) / 2);
			
			//Only the intersection of both right here
			box3->csgDifference(*box4);

			boxl->csgDifference(*box3);

			//Create the portals
			addPortals(m_Scene, *boxl, boxl->getRoot());

			//addPortals(m_Scene, *box, box->getRoot());
		}
	}

	void BSPEntity::render()
	{

	}
}
