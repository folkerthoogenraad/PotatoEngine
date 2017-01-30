#pragma once

#include "math/Triangle3.h"
#include "math/Vector3.h"
#include "math/Plane.h"
#include "math/Rational.h"

#include "logger/log.h" //Should be moved to somewhere else

#include <vector>
#include <string>
#include <memory>

#define BSP_DEBUG 1

namespace ftec {

	class BSP3;

	struct BSPFace {
		Planer m_Plane;

		std::vector<Vector3r> m_Vertices;

		std::string m_DebugTag;

		int m_ID;
	};

	struct BSPNode3 {
	public:
		std::shared_ptr<BSPNode3> m_Front;
		std::shared_ptr<BSPNode3> m_Back;

		BSPNode3 *m_Parent;

		size_t m_Index;
		BSP3 *m_BSP;
	public:
		void print(int tabs = 0);
		int cellcount();
		int solidcount();

		bool isSpace();
	private:
		bool insert(size_t index, bool allowFront = true, bool allowBack = true);
		void invert();

		bool removeWithoutId(int id);

		friend BSP3;
	};

	class BSP3 {

	private:
		std::vector<BSPFace> m_Planes;
		std::shared_ptr<BSPNode3> m_Root;

	public: //Should be private!
		//Decpricatedage
		/*void insert(const Triangle3r &triangle, BSPMaterial material = BSPMaterial::SOLID, const std::string &dbg = "Node", int id = 0, bool allowFront = true, bool allowBack = true)
		{
			//Create the needed plane
			BSPFacer ct = {
				Planer(triangle)
			};
			ct.m_Material = material;
			ct.m_Vertices.push_back(triangle.a);
			ct.m_Vertices.push_back(triangle.b);
			ct.m_Vertices.push_back(triangle.c);
			ct.m_ID = id;
			ct.m_DebugTag = dbg;

			m_Planes.push_back(std::move(ct));

			//If there is no BSP root yet, create the root
			if (!m_Root) {
				m_Root = std::make_shared<BSPNode3r>();
				m_Root->m_Index = 0;
				m_Root->m_BSP = this;
			}

			//Else, if there is a root, insert it into the root and let it figure out the rest from here
			else {
				m_Root->insert(m_Planes.size() - 1, allowFront, allowBack);
			}
		}*/
		
		//Use this instead
		void insert(BSPFace ct, const std::string &dbg = "Node", int id = 0, bool allowFront = true, bool allowBack = true);

		void resetID();
		void invert();


	public:
		int cellcount();
		int solidcount();
		
		BSP3 &csgUnion(const BSP3 &other);
		BSP3 &csgIntersection(const BSP3 &other);
		BSP3 &csgDifference(const BSP3 &other);

		BSPNode3 *getRoot() { return m_Root.get(); };
		const BSPFace &getPlane(int index) { return m_Planes[index]; }

		void print();

		friend BSPNode3;
	};

	std::unique_ptr<BSP3> makeBox(const Vector3r &position, const Vector3r extends);
}