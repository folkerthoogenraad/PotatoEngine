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

				LOG(indices[i].first << " : " << indices[i].second);

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

	static void addPortals(Scene *scene, BSP3<rational> &bsp, BSPNode3* node)
	{
		if (node->m_Front == nullptr){
			std::vector<std::pair<size_t, int>> indices;

			BSPNode3 *n = node;

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

	Vector3r a = Vector3r(0, 0, 4);
	Vector3r b = Vector3r(3, 0, 4);
	Vector3r c = Vector3r(4, 0, 2);
	Vector3r d = Vector3r(2, 0, 0);
	Vector3r e = Vector3r(2, 0, 3);

	void BSPEntity::onStart()
	{
		//OH BBY
		BSP3<rational> bsp;

		//Create the space
		{
			Vector3r offset = Vector3r(0, 1, 0);

			//Vector3r e = Vector3r(0, 0, 0);

			//Top and bottom
			bsp.insert(Triangle3r(
				a + offset, c + offset, d + offset * 2
			), BSPMaterial::SOLID, "Top");
			bsp.insert(Triangle3r(
				a, d, c
			), BSPMaterial::SOLID, "Bottom");

			//Box a
			bsp.insert(Triangle3r(
				a, b, a + offset
			), BSPMaterial::SOLID, "AB");
			bsp.insert(Triangle3r(
				b, c, b + offset
			), BSPMaterial::SOLID, "BC");
			bsp.insert(Triangle3r(
				c, d, c + offset
			), BSPMaterial::SOLID, "CD");
			bsp.insert(Triangle3r(
				d, e, d + offset
			), BSPMaterial::SOLID, "DE");
			bsp.insert(Triangle3r(
				e, a, e + offset
			), BSPMaterial::SOLID, "EA");
			/*bsp.insert(Triangle3r(
				e, a, e + offset
			));*/

			//Box b
			/*
			bsp.insert(Triangle3r(
				e, f, e + offset
			));
			bsp.insert(Triangle3r(
				f, h, f + offset
			));
			bsp.insert(Triangle3r(
				h, g, h + offset
			));
			bsp.insert(Triangle3r(
				g, e, g + offset
			));*/

			bsp.print();
		}
	
		//Create the "Portals"
		{
			addPortals(m_Scene, bsp, bsp.getRoot());
		}

	}

	void BSPEntity::render()
	{
		auto toFloat = [](const Vector3r &v) -> Vector3f {
			Vector3f out;
			out.x = v.x.convert_to<float>();
			out.y = v.y.convert_to<float>();
			out.z = v.z.convert_to<float>();
			return out;
		};

		Vector3f offset = Vector3f(0, 2, 0);

		Line3f line;

		line.a = toFloat(a);
		line.b = line.a + offset;
		Graphics::enqueueLine(line, Color32::red());
		line.a = toFloat(b);
		line.b = line.a + offset;
		Graphics::enqueueLine(line, Color32::red());
		line.a = toFloat(c);
		line.b = line.a + offset;
		Graphics::enqueueLine(line, Color32::red());
		line.a = toFloat(d);
		line.b = line.a + offset;
		Graphics::enqueueLine(line, Color32::red());
		line.a = toFloat(e);
		line.b = line.a + offset;
		Graphics::enqueueLine(line, Color32::red());
		

	}
}
