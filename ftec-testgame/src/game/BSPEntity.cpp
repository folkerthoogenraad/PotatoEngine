#include "BSPEntity.h"
#include "RationalPointCloudEntity.h"

#include "math/Rational.h"
#include "math/Ray3.h"
#include "math/BSP3.h"
#include "math/Line3.h"
#include "math/Vector4.h"

#include "scene/Scene.h"

#include "graphics/Graphics.h"

#include "logger/log.h"

namespace ftec {

	static inline void makeFromIndices(Scene *scene, BSP3<rational> &bsp, std::vector<std::pair<size_t, int>> indices) //std::pair<size_t, int> is index in getPlane(size_t) and the plane direction (1 or -1)
	{
		LOG("Ayy lmao");

		struct Intersection {
			int i, j, k;
			Vector3<rational> vertex;
		};
		std::vector<Intersection> intersections;

		for (int i = 0; i < indices.size(); i++){
			for (int j = i + 1; j < indices.size(); j++){
				auto &plane1 = bsp.getPlane(indices[i].first);
				auto &plane2 = bsp.getPlane(indices[j].first);

				auto rayResult = intersectRay(plane1.m_Plane, plane2.m_Plane);

				if (!rayResult)
					continue;

				for (int k = j + 1; k < indices.size(); k++){
					auto &plane3 = bsp.getPlane(indices[k].first);
					auto intersection = intersect(plane3.m_Plane, *rayResult);

					if (intersection) {
						intersections.push_back({
							(int)indices[i].first,(int)indices[j].first,(int)indices[k].first,
							*intersection
						});
					}
				}
			}
		}
	
		intersections.erase(std::remove_if(intersections.begin(), intersections.end(), 
			[&](const auto &test) {
			for (int i = 0; i < indices.size(); i++){
				int index = indices[i].first;

				if (test.i == index || test.j == index || test.k == index)
					continue;

				auto &plane = bsp.getPlane(index);

				if (plane.m_Plane.distanceFrom(test.vertex) * indices[i].second < 0) {
					return true;
				}
			}

			return false;
		}), intersections.end());

		LOG(intersections.size());
	
		if (intersections.size() > 3) {
			std::vector<Vector3<rational>> vertices;

			//Not sure if i can even do this
			for (int i = 0; i < intersections.size(); i++)
			{
				vertices.push_back(std::move(intersections[i].vertex));
			}

			scene->addEntity(std::make_unique<RationalPointCloudEntity>(vertices));
		}
		else {
			LOG("Attempting to create mesh, but amount of vertices is too low.");
		}
	}

	static void addPortals(Scene *scene, BSP3<rational> &bsp, BSPNode3<rational>* node)
	{
		if (node->m_Front == nullptr){
			std::vector<std::pair<size_t, int>> indices;

			BSPNode3<rational> *n = node;

			int dir = 1;

			while (n)
			{
				indices.push_back({ n->m_Index, dir});

				if (n->m_Parent) {
					if (n->m_Parent->m_Back.get() == n)
						dir = -1;
					else
						dir = 1;
				}
				n = n->m_Parent;
			}

			makeFromIndices(scene, bsp, indices);
		}

		if(node->m_Front)
			addPortals(scene, bsp, node->m_Front.get());

		if (node->m_Back)
			addPortals(scene, bsp, node->m_Back.get());
		
	}


	void BSPEntity::onStart()
	{
		//OH BBY

		//Create the space
#define INSERT(BSP, A, B, ID, FRONT, BACK) BSP.insert(Triangle3r(A, B, A + offset), BSPMaterial::SOLID, #A #B, ID, FRONT, BACK);
#define INSERT_HIGH(BSP, A, B, ID, FRONT, BACK) BSP.insert(Triangle3r(A, B, A + offset * 2), BSPMaterial::SOLID, #A #B, ID, FRONT, BACK);
#if 0
		{
			Vector3r offset = Vector3r(0, 1, 0);

			Vector3r a = Vector3r(0, 0, 4);
			Vector3r b = Vector3r(3, 0, 4);
			Vector3r c = Vector3r(4, 0, 2);
			Vector3r d = Vector3r(2, 0, 0);
			Vector3r e = Vector3r(2, 0, 3);


			//Top and bottom
			bsp.insert(Triangle3r(
				a + offset, c + offset, d + offset * 2
			), BSPMaterial::SOLID, "Top");
			bsp.insert(Triangle3r(
				a, d, c
			), BSPMaterial::SOLID, "Bottom");

			//Box a
			INSERT(a, b);
			INSERT(b, c);
			INSERT(c, d);
			INSERT(d, e);
			INSERT(e, a);

			bsp.print();
		}
#endif 
#if 0
		BSP3<rational> bsp;
		{
			Vector3r offset = Vector3r(0, 1, 0);

			Vector3r a = Vector3r(0, 0, 2);
			Vector3r b = Vector3r(2, 0, 2);
			Vector3r c = Vector3r(2, 0, 0);
			Vector3r d = Vector3r(0, 0, 0);
			Vector3r e = Vector3r(1, 0, 3);
			Vector3r f = Vector3r(3, 0, 3);
			Vector3r g = Vector3r(3, 0, 1);
			Vector3r h = Vector3r(1, 0, 1);

			//Top and bottom
			bsp.insert(Triangle3r(
				a + offset, c + offset, d + offset
			), BSPMaterial::SOLID, "Top");
			bsp.insert(Triangle3r(
				a, d, c
			), BSPMaterial::SOLID, "Bottom");

			//Box a
			INSERT(bsp, a, b, 0, true, true);
			INSERT(bsp, b, c, 0, true, true);
			INSERT(bsp, c, d, 0, true, true);
			INSERT(bsp, d, a, 0, true, true);

			BSP3<rational> bsp2;

			bsp2.insert(Triangle3r(
				e + offset, f + offset, g + offset * 2
			), BSPMaterial::SOLID, "Top");
			bsp2.insert(Triangle3r(
				e, g, f
			), BSPMaterial::SOLID, "Bottom");

			INSERT(bsp2, e, f, 0, true, true);
			INSERT_HIGH(bsp2, f, g, 0, true, true);
			INSERT_HIGH(bsp2, g, h, 0, true, true);
			INSERT(bsp2, h, e, 0, true, true);

			/* ADD
			INSERT(bsp, e, f, 0, false, true);
			INSERT(bsp, f, g, 0, false, true);
			INSERT(bsp, g, h, 0, false, true);
			INSERT(bsp, h, e, 0, false, true);
			/* */

			/* SUBTRACT
			INSERT(e, h, 1, true, false);
			INSERT(f, e, 1, true, false);
			INSERT(g, f, 1, true, false);
			INSERT(h, g, 1, true, false);
			/* */

			/* INTERSECTION
			INSERT(e, f, 1, true, false);
			INSERT(f, g, 1, true, false);
			INSERT(g, h, 1, true, false);
			INSERT(h, e, 1, true, false);
			/* */

			bsp.csgUnion(bsp2);

			//bsp.print();
			//addPortals(m_Scene, bsp2, bsp.getRoot());
			//addPortals(m_Scene, bsp2, bsp.getRoot());
		}
#endif
		{
			auto box = makeBox<rational>(Vector3r(0, 0, 0), Vector3r(1, 1, 1));

			auto box2 = makeBox<rational>(Vector3r(1, 1, 1), Vector3r(1, 1, 1));

			box->csgUnion(*box2);


			addPortals(m_Scene, *box, box->getRoot());
		}

	}

	void BSPEntity::render()
	{

	}
}
