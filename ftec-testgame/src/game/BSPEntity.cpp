#include "BSPEntity.h"
#include "RationalPointCloudEntity.h"

#include "math/Rational.h"
#include "math/BSP3.h"

#include "scene/Scene.h"

#include "logger/log.h"

namespace ftec {

	static inline void makeFromIndices(Scene *scene, BSP3<rational> &bsp, std::vector<size_t> indices)
	{
		for (int i = 0; i < indices.size(); i++)
		{
			for (int j = i + 1; j < indices.size(); j++)
			{

			}
		}
	}

	static void addPortals(Scene *scene, BSP3<rational> &bsp, BSPNode3* node)
	{
		if (node->m_Front == nullptr){
			std::vector<size_t> indices;

			BSPNode3 *n = node;

			while (n)
			{
				indices.push_back(n->m_Index);
				n = n->m_Parent;
			}

			makeFromIndices(scene, bsp, indices);
		}
		else {
			addPortals(scene, bsp, node->m_Front.get());
		}
	}

	void BSPEntity::onStart()
	{
		//OH BBY
		BSP3<rational> bsp;

		//Create the space
		{
			Vector3r offset = Vector3r(0, 0, 1);

			Vector3r a = Vector3r(0, 2, 0);
			Vector3r b = Vector3r(2, 2, 0);
			Vector3r c = Vector3r(0, 0, 0);
			Vector3r d = Vector3r(2, 0, 0);

			Vector3r e = Vector3r(1, 3, 0);
			Vector3r f = Vector3r(3, 3, 0);
			Vector3r g = Vector3r(1, 1, 0);
			Vector3r h = Vector3r(3, 1, 0);

			Vector3r phantom = Vector3r(0, 3, 0);

			//Top and bottom
			bsp.insert(Triangle3r(
				c + offset, phantom + offset, f + offset
			));
			bsp.insert(Triangle3r(
				phantom, c, f
			));

			//Box a
			bsp.insert(Triangle3r(
				a, b, a + offset
			));
			bsp.insert(Triangle3r(
				b, d, b + offset
			));
			bsp.insert(Triangle3r(
				d, c, d + offset
			));
			bsp.insert(Triangle3r(
				c, a, c + offset
			));

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

			LOG(bsp.cellcount());
		}
	
		//Create the "Portals"
		{
			addPortals(m_Scene, bsp, bsp.getRoot());
		}

	}
}
