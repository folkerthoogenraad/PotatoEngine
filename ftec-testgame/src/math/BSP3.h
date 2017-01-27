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
	struct BSPFace {
		Plane<T> m_Plane;

		std::vector<Vector3<T>> m_Vertices;

		std::string m_DebugTag;

		int m_ID;
		BSPMaterial m_Material;
	};

	//This can really benefit from more tight packing and inline nodes (unlike these nodes)
	//This can be shared between BSP2 and BSP3, but whatever
	template <typename T>
	struct BSPNode3 {
	
	public: //TODO make this private!

		std::shared_ptr<BSPNode3<T>> m_Front;
		std::shared_ptr<BSPNode3<T>> m_Back;

		BSPNode3<T> *m_Parent;

		size_t m_Index;
		BSP3<T> *m_BSP;
	public:
		void print(int tabs = 0)
		{
			for (int i = 0; i < tabs; i++)
				std::cout << ' ' << ' ';

			std::cout << m_BSP->getPlane(m_Index).m_DebugTag << '(' << m_Index << ')' << ":" << std::endl;

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
		int solidcount()
		{
			int c = 0;
			
			if (m_Front)
				c += m_Front->solidcount();
			else
				c += 1;
			
			if (m_Back)
				c += m_Back->soldcount();

			return c;
		}

	private:
		void insert(size_t index, bool allowFront = true, bool allowBack = true)
		{
			BSPFace<T> &self = m_BSP->m_Planes[m_Index];
			BSPFace<T> &other = m_BSP->m_Planes[index];

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
			for (const auto &v : other.m_Vertices)
			{
				compare(insertTest(v));
			}
			
			auto create = [&](std::shared_ptr<BSPNode3> &position, bool allowedToCreateNew) {
				if (position) {
					position->insert(index, allowFront, allowBack);
				}
				else if(allowedToCreateNew || self.m_ID == other.m_ID){
					position = std::make_shared<BSPNode3>();
					position->m_Parent = this;
					position->m_Index = index;
					position->m_BSP = m_BSP;
				}
			};

			if (frontCount == 0 && backCount == 0) {
				//TODO handle this case
				//Look at a few things, like the normal direction might be important?
				//assert(false);
				LOG("Unhandled case! might be important soon™");
			}
			if (frontCount > 0){
				create(m_Front, allowFront);
			}
			if (backCount > 0) {
				create(m_Back, allowBack);
			}
		}
		void invert()
		{
			//Planes should already be flipped right now
			//Because planes are double references, its possible to accidentally double flip this.
			auto t = m_Front;
			m_Front = m_Back;
			m_Back = t;

			if (m_Front)
				m_Front->invert();
			if (m_Back)
				m_Back->invert();
		}

		friend BSP3<T>;
	};

	//TODO clean this up, ofcourse
	template <typename T>
	class BSP3 {

	private:
		std::vector<BSPFace<T>> m_Planes;
		std::shared_ptr<BSPNode3<T>> m_Root;

	public: //Should be private!
		//Decpricatedage
		void insert(const Triangle3<T> &triangle, BSPMaterial material = BSPMaterial::SOLID, const std::string &dbg = "Node", int id = 0, bool allowFront = true, bool allowBack = true)
		{
			//Create the needed plane
			BSPFace<T> ct = {
				Plane<T>(triangle)
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
				m_Root = std::make_shared<BSPNode3<T>>();
				m_Root->m_Index = 0;
				m_Root->m_BSP = this;
			}

			//Else, if there is a root, insert it into the root and let it figure out the rest from here
			else {
				m_Root->insert(m_Planes.size() - 1, allowFront, allowBack);
			}
		}
		
		//Use this instead
		void insert(BSPFace<T> ct, const std::string &dbg = "Node", int id = 0, bool allowFront = true, bool allowBack = true)
		{
			ct.m_ID = id;
			ct.m_DebugTag = dbg;
			m_Planes.push_back(std::move(ct));

			//If there is no BSP root yet, create the root
			if (!m_Root) {
				m_Root = std::make_shared<BSPNode3<T>>();
				m_Root->m_Index = 0;
				m_Root->m_BSP = this;
			}

			//Else, if there is a root, insert it into the root and let it figure out the rest from here
			else {
				m_Root->insert(m_Planes.size() - 1, allowFront, allowBack);
			}
		}

		void resetID()
		{
			for (auto &p : m_Planes)
			{
				p.m_ID = 0;
			}
		}
		void invert()
		{
			for (auto &p : m_Planes)
			{
				p.m_Plane.flip();
			}

			if (m_Root)
				m_Root->invert();
		}


	public:
		int cellcount()
		{
			return m_Root ? m_Root->cellcount() : 0;
		}
		int solidcount()
		{
			if(m_Root)
				return m_Root->solidcount();
			return 0;
		}

		BSP3<T> &csgUnion(const BSP3<T> &other)
		{
			for (const auto &p : other.m_Planes){
				insert(p, p.m_DebugTag, 1, false, true);
			}

			resetID();

			return *this;
		}

		BSP3<T> &csgIntersection(const BSP3<T> &other)
		{

			return *this;
		}

		BSP3<T> &csgDifference(const BSP3<T> &other)
		{

			return *this;
		}

		
		BSPNode3<T> *getRoot() { return m_Root.get(); };
		const BSPFace<T> &getPlane(int index) { return m_Planes[index]; }

		void print()
		{
			if (m_Root) {
				m_Root->print(0);
			}
			else {
				LOG("BSP Empty.");
			}
		}

		friend BSPNode3<T>;
	};

	template <typename T>
	BSP3<T> makeBox(const Vector3<T> &position, const Vector3<T> extends)
	{
		BSP3<T> bsp;

		BSPFace<T> face;

		auto makeFace = [&](const Vector3<T> &a, const Vector3<T> &b, const Vector3<T> &c, const Vector3<T> &d) {
			face.m_Vertices.push_back(a);
			face.m_Vertices.push_back(b);
			face.m_Vertices.push_back(c);
			face.m_Vertices.push_back(d);

			face.m_Plane = Plane<T>(Triangle3<T>(a,b,c));
		};

		const Vector3<T> a(position.x - extends.x, position.y - extends.y, position.z - extends.z);
		const Vector3<T> b(position.x + extends.x, position.y - extends.y, position.z - extends.z);
		const Vector3<T> c(position.x + extends.x, position.y - extends.y, position.z + extends.z);
		const Vector3<T> d(position.x - extends.x, position.y - extends.y, position.z + extends.z);

		const Vector3<T> e(position.x - extends.x, position.y + extends.y, position.z - extends.z);
		const Vector3<T> f(position.x + extends.x, position.y + extends.y, position.z - extends.z);
		const Vector3<T> g(position.x + extends.x, position.y + extends.y, position.z + extends.z);
		const Vector3<T> h(position.x - extends.x, position.y + extends.y, position.z + extends.z);

		makeFace(a, b, c, d);
		bsp.insert(face, "Bottom");

		makeFace(e, h, g, f);
		bsp.insert(face, "Top");

		makeFace(e, a, b, f);
		bsp.insert(face, "Front");

		makeFace(h, d, c, g);
		bsp.insert(face, "Back");

		makeFace(b, f, g, c);
		bsp.insert(face, "Left");

		makeFace(a, d, h, e);
		bsp.insert(face, "Right");

		bsp.print();

		return bsp;
	}

}