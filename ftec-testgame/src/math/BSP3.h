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

		std::string m_DebugTag;

		//ID shouldn't be used.
		int m_ID;
	};

	enum class BSPDirection {
		BACK = -1,
		ON = 0,
		FRONT = 1
	};

	struct BSPCell3 {
		struct PlaneDirectionRef {
			int planeIndex;

			BSPDirection direction;
		};
		struct BSPIntersection {
			int i, j, k;

			Vector3r vertex;
		};

		BSP3 *m_BSP;
		std::vector<BSPIntersection> m_Intersections;
	};

	struct BSPNode3 {
	public:
		std::shared_ptr<BSPNode3> m_Front;
		std::shared_ptr<BSPNode3> m_Back;

		std::vector<Vector3r> m_Vertices;

		BSPNode3 *m_Parent;

		BSP3 *m_BSP;
		size_t m_Index;
	public:
		void print(int tabs = 0);
		int cellcount() const;
		int solidcount() const;

		BSPDirection onSide(const Vector3r &) const;

		void forEachCell(std::function<void(BSPNode3 *)> &func);
		void forEachCell(std::function<void(const BSPNode3 *)> &func) const;

		//I don't like the name of this function, but it calculates the cell vertices.
		BSPCell3 calculateCell();

		bool isSpace() const;
	private:
		bool insert(std::shared_ptr<BSPNode3> node);

		bool insert(size_t index, bool allowFront = true, bool allowBack = true);
		void invert();

		bool removeWithoutID(int id);
		bool containsID(int id);

		void testFace(const BSPFace &self, const BSPFace &other, int &frontCount, int &backCount);

		//bool clip(const std::vector<int> &indices); //Works only for convex

		bool clip(const BSP3 &bps);

		friend BSP3;
	};

	class BSP3 {

	private:
		std::vector<BSPFace> m_Planes;
		std::shared_ptr<BSPNode3> m_Root;

	public: //Should be private!
		
		//Use this instead
		void insert(BSPFace ct, const std::string &dbg = "Node", int id = 0, bool allowFront = true, bool allowBack = true);
		
		void insert(std::vector<Vector3r> verts, const std::string &dbg = "Node");

		void resetID();
		void invert();

	public:
		int cellcount() const;
		int solidcount() const;

		bool isConvex() const;
		
		BSP3 &csgUnion(const BSP3 &other);
		BSP3 &csgIntersection(const BSP3 &other);
		BSP3 &csgDifference(const BSP3 &other);

		void forEachCell(std::function<void(BSPNode3 *)> func);
		void forEachCell(std::function<void(const BSPNode3 *)> func) const;

		BSPNode3 *getRoot() { return m_Root.get(); };
		const BSPFace &getPlane(int index) const { return m_Planes[index]; }

		void print();

		friend BSPNode3;
	};

	std::unique_ptr<BSP3> makeBox(const Vector3r &position, const Vector3r extends);
	std::unique_ptr<BSP3> makeCylinder(const Vector3r &position, const Vector3r extends);
	std::unique_ptr<BSP3> makeSphere(const Vector3r &position, const Vector3r extends);
}