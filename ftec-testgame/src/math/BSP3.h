#pragma once

#include "math/Triangle3.h"
#include "math/Vector3.h"
#include "math/Plane.h"

#include "logger/log.h" //Should be moved to somewhere else

#include <vector>
#include <string>
#include <memory>

namespace ftec {

	template <typename T>
	class BSP3;

	enum class BSPMaterial
	{
		AIR = 0,
		SOLID = 1
	};

	template <typename T>
	struct BSPPlane {
		//Triangle3<T> m_Triangle;
		//Vector3<T> m_Normal;
		Plane<T> m_Plane;

		BSPMaterial m_Material;
	};

	//This can really benefit from more tight packing and inline nodes (unlike these nodes)
	//This can be shared between BSP2 and BSP3, but whatever
	struct BSPNode3 {
		std::shared_ptr<BSPNode3> m_Front;	//8 bytes
		std::shared_ptr<BSPNode3> m_Back;	//8 bytes

		std::string m_DebugTag;
		BSPNode3 *m_Parent;					//8 bytes

		size_t m_Index;						//8 bytes

	public:
		template <typename T>
		void insert(BSP3<T> &bsp, size_t index, const Vector3<T> &a, const Vector3<T> &b, const Vector3<T> &c, const std::string &dbg)
		{
			BSPPlane<T> &self = bsp.m_Planes[m_Index];
			BSPPlane<T> &other = bsp.m_Planes[index];

			int frontCount = 0;
			int backCount = 0;
			
			auto insertTest = [&self](const Vector3<T> &point) -> T{
				return self.m_Plane.distanceFrom(point);
			};
			auto compare = [&frontCount, &backCount](const T &v) {
				if (v > 0)
					frontCount++;
				else if (v < 0)
					backCount++;
			};

			//Test the triangle
			compare(insertTest(a));
			compare(insertTest(b));
			compare(insertTest(c));
			
			auto create = [&](std::shared_ptr<BSPNode3> &position) {
				if (position) {
					position->insert(bsp, index, a, b, c, dbg);
				}
				else {
					position = std::make_shared<BSPNode3>();
					position->m_Parent = this;
					position->m_Index = index;
					position->m_DebugTag = dbg;
				}
			};

			if (frontCount == 0 && backCount == 0) {
				//TODO handle this case
				//Look at a few things, like the normal direction might be important?
				//assert(false);
			}
			if (frontCount > 0){
				create(m_Front);
			}
			if (backCount > 0) {
				create(m_Back);
			}
		}

		void print(int tabs = 0)
		{
			for (int i = 0; i < tabs; i++)
				std::cout << ' ' << ' ';

			std::cout << m_DebugTag << '(' << m_Index << ')' << ":" << std::endl;

			auto printSide = [&](std::shared_ptr<BSPNode3> &node) {
				if (node) {
					node->print(tabs + 1);
				}
				else {
					for (int i = 0; i < tabs + 1; i++)
						std::cout << ' ' << ' ';
					std::cout << "empty" << std::endl;
				}
			};

			printSide(m_Front);
			printSide(m_Back);
		}
		int cellcount()
		{
			int result = 0;

			if (m_Front)
				result += m_Front->cellcount();
			else
				result += 1;

			if (m_Back)
				result += m_Back->cellcount();
			else
				result += 1;

			return result;
		}
	};

	template <typename T>
	class BSP3 {

	private:
		std::vector<BSPPlane<T>> m_Planes;
		std::shared_ptr<BSPNode3> m_Root;

	public:

		void insert(const Triangle3<T> &triangle, BSPMaterial material = BSPMaterial::SOLID, const std::string &dbg = "Node")
		{
			BSPPlane<T> ct = {
				Plane<T>(triangle)
			};
			ct.m_Material = material;
			//ct.m_Normal = ct.m_Triangle.normal();
			m_Planes.push_back(std::move(ct));

			if (!m_Root) {
				m_Root = std::make_shared<BSPNode3>();
				m_Root->m_Index = 0;
				m_Root->m_DebugTag = dbg;
			}
			else {
				m_Root->insert(*this, m_Planes.size() - 1, triangle.a, triangle.b, triangle.c, dbg);
			}
		}
		int cellcount()
		{
			return m_Root ? m_Root->cellcount() : 0;
		}

		BSPNode3 *getRoot() { return m_Root.get(); };
		const BSPPlane<T> &getPlane(int index) { return m_Planes[index]; }

		void print()
		{
			if (m_Root) {
				m_Root->print(0);
			}
			else {
				LOG("BSP Empty.");
			}
		}

		friend BSPNode3;
	};

}