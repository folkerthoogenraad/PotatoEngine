#include "BSP3.h"

#include "math/collision.h"
#include "math/Ray3.h"
#include "math/Line3.h"

namespace ftec {
	void BSPNode3::print(int tabs)
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

	int BSPNode3::cellcount() const
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

	int BSPNode3::solidcount() const
	{
		int c = 0;

		if (m_Front)
			c += m_Front->solidcount();
		else
			c += 1;

		if (m_Back)
			c += m_Back->solidcount();

		return c;
	}

	BSPDirection BSPNode3::onSide(const Vector3r &side) const
	{
		//This function tho
		int s = m_BSP->getPlane(m_Index).m_Plane.distanceFrom(side).sign();

		//A little bit of explaination:
		//
		//The distanceFrom can be negative
		//So if we take the sign from the distance, we have enough information
		//Because there are only three options, -1, 0, 1
		//And that is enough

		return (BSPDirection) s;
	}

	void BSPNode3::forEachCell(std::function<void(BSPNode3*)> &func)
	{
		if (m_Front == nullptr)
			func(this);
		else
			m_Front->forEachCell(func);

		if (m_Back != nullptr)
			m_Back->forEachCell(func);
	}
	void BSPNode3::forEachCell(std::function<void(const BSPNode3*)> &func) const
	{
		if (m_Front == nullptr)
			func(this);
		else
			m_Front->forEachCell(func);

		if (m_Back != nullptr)
			m_Back->forEachCell(func);
	}

	BSPCell3 BSPNode3::calculateCell()
	{
		assert(isSpace());
		
		BSPCell3 cell;
		cell.m_BSP = m_BSP;

		struct PlaneDirectionRef {
			size_t planeIndex;

			enum class Direction{
				BACK = -1,
				FRONT = 1
			} direction;
		};

		std::vector<PlaneDirectionRef> indicesAndDirection;

		//Find all the indices for all my parents.
		{
			BSPNode3 *n = this;

			//If we are a space we are, by definition, in front.
			PlaneDirectionRef::Direction dir = PlaneDirectionRef::Direction::FRONT; 

			while (n)
			{
				indicesAndDirection.push_back({ n->m_Index, dir });

				//Find the direction we are.
				if (n->m_Parent) {
					if (n->m_Parent->m_Back.get() == n)
						dir = PlaneDirectionRef::Direction::BACK;
					else
						dir = PlaneDirectionRef::Direction::FRONT;
				}

				n = n->m_Parent;
			}
			//NOTE: this 'calculation' is far from perfect and even a little hacky
			//however, there is no reason not to do it, the rest of the function is so
			//much slower, that this is practically irrelevant.
		}

		//Now find all the intersection points.
		{
			//This part is very very time consuming.
			for (int i = 0; i < indicesAndDirection.size(); i++) {
				for (int j = i + 1; j < indicesAndDirection.size(); j++) {
					auto &plane1 = m_BSP->getPlane(indicesAndDirection[i].planeIndex);
					auto &plane2 = m_BSP->getPlane(indicesAndDirection[j].planeIndex);

					auto rayResult = intersectRay(plane1.m_Plane, plane2.m_Plane);

					if (!rayResult)
						continue;

					for (int k = j + 1; k < indicesAndDirection.size(); k++) {
						auto &plane3 = m_BSP->getPlane(indicesAndDirection[k].planeIndex);

						auto intersection = intersect(plane3.m_Plane, *rayResult);

						if (intersection) {
							cell.m_Intersections.push_back({
								(int)indicesAndDirection[i].planeIndex,
								(int)indicesAndDirection[j].planeIndex,
								(int)indicesAndDirection[k].planeIndex,
								*intersection
							});
						}
					}
				}
			}
			
			//And then there is this part, which makes it even worse
			cell.m_Intersections.erase(std::remove_if(cell.m_Intersections.begin(), cell.m_Intersections.end(),
				[&](const BSPCell3::BSPIntersection &test) {
				for (int i = 0; i < indicesAndDirection.size(); i++) {
					int index = indicesAndDirection[i].planeIndex;

					if (test.i == index || test.j == index || test.k == index)
						continue;

					auto &plane = m_BSP->getPlane(index);
					int s = plane.m_Plane.distanceFrom(test.vertex).sign();

					if (s != (int)indicesAndDirection[i].direction && s != 0) {
						return true;
					}
				}
				return false;
			
			}), cell.m_Intersections.end());
		}

		//And then return the result
		return std::move(cell);
	}

	bool BSPNode3::isSpace() const
	{
		return m_Front == nullptr;
	}

	bool BSPNode3::insert(std::shared_ptr<BSPNode3> node) //TODO allow front and allow back stuff
	{
		assert(node->m_Vertices.size() >= 3);

		const BSPFace &face = m_BSP->getPlane(m_Index);

		std::vector<int> intersectionIndices;
		std::vector<Vector3r> intersectionPoints;

		std::vector<BSPDirection> directions;

		bool hasFront = false;
		bool hasBack = false;
		int onCount = 0;

		//This is one operation too many, so this should be reworked.
		//We test two points too many
		BSPDirection previous = onSide(node->m_Vertices[0]);

		//Test all the points
		for (int index = 0; index <= node->m_Vertices.size(); index++) {

			int i = index % node->m_Vertices.size();

			BSPDirection dir = onSide(node->m_Vertices[i]);

			if (dir == BSPDirection::ON)
				onCount++;

			if (dir == BSPDirection::BACK) {
				hasBack = true;
				if (previous == BSPDirection::FRONT) {
					intersectionIndices.push_back(i);
				}
			}

			if (dir == BSPDirection::FRONT) {
				hasFront = true;
				
				if (previous == BSPDirection::BACK) {
					intersectionIndices.push_back(i);
				}
			}

			directions.push_back(dir);
			previous = dir;
		}

		assert(intersectionIndices.size() <= 2);

		for (int i = 0; i < intersectionIndices.size(); i++){
			int index1 = (intersectionIndices[i] - 1) % m_Vertices.size();
			int index2 = (intersectionIndices[i]) % m_Vertices.size();

			auto res = intersect(face.m_Plane, Line3r(m_Vertices[index1], m_Vertices[index2]));
			
			assert(res);

			intersectionPoints.push_back(*res);
		}

		assert(intersectionIndices.size() == intersectionPoints.size());

		auto put = [&](std::shared_ptr<BSPNode3> &target, std::shared_ptr<BSPNode3> &source) {
			if (!target) {
				target = source;
				target->m_Parent = this;
			}
			else {
				target->insert(source);
			}
		};

		//-------------------------------------------------------------------
		// Insert in the back
		//-------------------------------------------------------------------
		if (hasBack && !hasFront) {
			put(m_Back, node);
		}

		//-------------------------------------------------------------------
		// Insert in the front
		//-------------------------------------------------------------------
		else if (hasFront && !hasBack) {
			put(m_Front, node);
		}

		//-------------------------------------------------------------------
		// Split the polygon
		//-------------------------------------------------------------------
		else if (hasBack && hasFront) {
			//Split the polygon.
			assert(onCount <= 2);
			assert(intersectionPoints.size() - onCount == 0);

			auto front = std::make_shared<BSPNode3>();
			auto back = std::make_shared<BSPNode3>();


		}

		//-------------------------------------------------------------------
		// Coplaner panic
		//-------------------------------------------------------------------
		else { //Oh my, we are coplanar. Panic!
			assert(false);
		}

		return false;
	}

	bool BSPNode3::insert(size_t index, bool allowFront, bool allowBack)
	{
		BSPFace &self = m_BSP->m_Planes[m_Index];
		BSPFace &other = m_BSP->m_Planes[index];

		int frontCount = 0;
		int backCount = 0;

		//testFace(self, other, frontCount, backCount);
		
		auto create = [&](std::shared_ptr<BSPNode3> &position, bool allowedToCreateNew) -> bool {
			if (position) {
				return position->insert(index, allowFront, allowBack);
			}
			else if (allowedToCreateNew || self.m_ID == other.m_ID) {
				position = std::make_shared<BSPNode3>();
				position->m_Parent = this;
				position->m_Index = index;
				position->m_BSP = m_BSP;

				return true;
			}

			return false;
		};

		bool c = false;
		
		if (frontCount == 0 && backCount == 0) {
			//TODO handle this case
			//Look at a few things, like the normal direction might be important?
			//assert(false);
			LOG("This case is really weird. The planes are coplanar. ");
			LOG("Maybe add multiple planes per face.");

			return false;
		}
		
		if (frontCount > 0) {
			c = create(m_Front, allowFront) || c;
		}
		if (backCount > 0) {
			c = create(m_Back, allowBack) || c;
		}

		return c;
	}
	void BSPNode3::invert()
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
	bool BSPNode3::removeWithoutID(int id)
	{
		BSPFace &self = m_BSP->m_Planes[m_Index];

		if (self.m_ID == id)
			return false;

		if (m_Front) {
			if (m_Front->removeWithoutID(id)) {
				m_Front.reset();
			}
		}

		if (m_Back) {
			if (m_Back->removeWithoutID(id)) {
				m_Back.reset();
			}
		}

		if (!m_Front && !m_Back)
			return true;

		return false;
	}
	bool BSPNode3::containsID(int id)
	{
		BSPFace &self = m_BSP->m_Planes[m_Index];

		if (self.m_ID == id)
			return true;

		if (m_Front && m_Front->containsID(id))
			return true;
		if (m_Back && m_Back->containsID(id))
			return true;

		return false;
	}
	
#if 0
	void BSPNode3::testFace(const BSPFace & plane, const BSPFace &vertices, int & frontCount, int & backCount)
	{
		auto insertTest = [&plane](const Vector3r &point) -> rational {
			return plane.m_Plane.distanceFrom(point);
		};
		auto compare = [&frontCount, &backCount](const rational &v) {
			int s = v.sign();

			if (s > 0)
				frontCount++;
			else if (s < 0)
				backCount++;
		};

		//Test the triangle
		for (const auto &v : vertices.m_Vertices)
		{
			//We calculate the full distance stuff, however, we only use the sign
			//We might be able to reduce this a bit.

			if (frontCount > 0 && backCount > 0)
				break;

			compare(insertTest(v));
		}

	}
#endif

	/*bool BSPNode3::clip(const std::vector<int> &indices)
	{
		if (m_Front && m_Front->clip(indices))
			m_Front.reset();

		if (m_Back && m_Back->clip(indices))
			m_Back.reset();

		if (!m_Front && !m_Back && !containsID(1)) { //Hardcoded contains ID :')
			BSPFace &self = m_BSP->m_Planes[m_Index];

			int frontCount = 0;
			int backCount = 0;

			for (auto index : indices) {
				BSPFace &other = m_BSP->m_Planes[index];
				testFace(other, self, frontCount, backCount);

				if (frontCount > 0)
					break;
			}

			if (frontCount == 0 && backCount > 0) {
				return true;
			}
		}

		return false;
	}*/

	//Removes everything inside the BSP
	bool BSPNode3::clip(const BSP3 & bsp)
	{
#if 0
		if (m_Front && m_Front->clip(bsp))
			m_Front.reset();

		if (m_Back && m_Back->clip(bsp))
			m_Back.reset();

		if (!m_Front && !m_Back) {

			BSPFace &self = m_BSP->m_Planes[m_Index];

			LOG("Testing " << self.m_DebugTag);
			
			bool done = false;

			bsp.forEachCell([&](const BSPNode3 *node) {
				if (done)
					return;

				int dir = 1;

				while (node) {
					const BSPFace &other = bsp.getPlane(node->m_Index);

					int frontCount = 0;
					int backCount = 0;
					
					if (dir == 1) {
						testFace(other, self, frontCount, backCount);
					}
					if (dir == -1){
						testFace(other, self, backCount, frontCount);
					}

					if (frontCount == 0 && backCount > 0) {
						done = true;
						break;
					}

					if (node->m_Parent) {
						if (node->m_Parent->m_Front.get() == node)
							dir = 1;
						else
							dir = -1;
					}

					node = node->m_Parent;
				}
			});

			return false;
		}

		return false;
#endif
		return false;
	}
	void BSP3::insert(BSPFace ct, const std::string & dbg, int id, bool allowFront, bool allowBack)
	{
		ct.m_ID = id;
		ct.m_DebugTag = dbg;
		m_Planes.push_back(std::move(ct));

		//If there is no BSP root yet, create the root
		if (!m_Root) {
			m_Root = std::make_shared<BSPNode3>();
			m_Root->m_Index = 0;
			m_Root->m_BSP = this;
		}

		//Else, if there is a root, insert it into the root and let it figure out the rest from here
		else {
			bool i = m_Root->insert(m_Planes.size() - 1, allowFront, allowBack);

			if (!i)
				m_Planes.pop_back();
		}
	}

	void BSP3::insert(std::vector<Vector3r> verts, const std::string & dbg)
	{
		assert(verts.size() > 0);
		
		m_Planes.emplace_back();
		BSPFace &face = m_Planes.back();

		face.m_DebugTag = dbg;
		face.m_ID = 0;
		face.m_Plane = Planer(verts[0], verts[1], verts[2]);

		auto node = std::make_shared<BSPNode3>();
		node->m_BSP = this;
		node->m_Index = m_Planes.size() - 1;
		node->m_Vertices = std::move(verts);
		
		if (m_Root)
			m_Root->insert(node);
		else
			m_Root = node;
	}

	void BSP3::resetID()
	{
		for (auto &p : m_Planes)
		{
			p.m_ID = 0;
		}
	}
	void BSP3::invert()
	{
		for (auto &p : m_Planes)
		{
			p.m_Plane.flip();
		}

		if (m_Root)
			m_Root->invert();
	}
	int BSP3::cellcount() const
	{
		return m_Root ? m_Root->cellcount() : 0;
	}
	int BSP3::solidcount() const
	{
		if (m_Root)
			return m_Root->solidcount();
		return 0;
	}

	bool BSP3::isConvex() const
	{
		return solidcount() == 1;
	}
	
	BSP3 & BSP3::csgUnion(const BSP3 & other)
	{
		if (!other.isConvex())
			LOG("Ohter BSP is not convex!");
		
		for (const BSPFace &p : other.m_Planes) {
			insert(p, p.m_DebugTag, 1, false, true);
		}

		resetID();

		return *this;
	}
	BSP3 & BSP3::csgIntersection(const BSP3 & other)
	{
		if (!other.isConvex())
			LOG("Ohter BSP is not convex!");

		for (const BSPFace &p : other.m_Planes) {
			insert(p, p.m_DebugTag, 1, true, false);
		}

		resetID();

		return *this;
	}
	BSP3 & BSP3::csgDifference(const BSP3 & other)
	{
		if (!other.isConvex())
			LOG("Other BSP is not convex!");

		if (m_Root->clip(other)) {
			m_Root = nullptr;
		}

		//Keep in mind, we copy here!
		for (BSPFace p : other.m_Planes) {
			p.m_Plane.flip();	
			
			insert(p, p.m_DebugTag, 1, true, false); //Even better, double copy
		}


		resetID();

		return *this;
	}

	void BSP3::forEachCell(std::function<void(BSPNode3 *)> func)
	{
		if (m_Root)
			m_Root->forEachCell(func);
	}
	void BSP3::forEachCell(std::function<void(const BSPNode3 *)> func) const
	{
		if (m_Root)
			m_Root->forEachCell(func);
	}

	void BSP3::print()
	{
		if (m_Root) {
			m_Root->print(0);
		}
		else {
			LOG("BSP Empty.");
		}
	}

	std::unique_ptr<BSP3> makeBox(const Vector3r & position, const Vector3r extends)
	{
		auto bsp = std::make_unique<BSP3>();

		const Vector3r a(position.x - extends.x, position.y - extends.y, position.z - extends.z);
		const Vector3r b(position.x + extends.x, position.y - extends.y, position.z - extends.z);
		const Vector3r c(position.x + extends.x, position.y - extends.y, position.z + extends.z);
		const Vector3r d(position.x - extends.x, position.y - extends.y, position.z + extends.z);

		const Vector3r e(position.x - extends.x, position.y + extends.y, position.z - extends.z);
		const Vector3r f(position.x + extends.x, position.y + extends.y, position.z - extends.z);
		const Vector3r g(position.x + extends.x, position.y + extends.y, position.z + extends.z);
		const Vector3r h(position.x - extends.x, position.y + extends.y, position.z + extends.z);


		bsp->insert({ a, b, c, d }, "Bottom");

		bsp->insert({ e, h, g, f }, "Top");

		bsp->insert({ a, e, f, b }, "Front");

		bsp->insert({ c, g, h, d }, "Back");

		bsp->insert({ b, f, g, c }, "Left");

		bsp->insert({ a, d, h, e }, "Right");

		return std::move(bsp);
	}

#if 0	
	std::unique_ptr<BSP3> makeCylinder(const Vector3r & position, const Vector3r extends)
	{
		auto bsp = std::make_unique<BSP3>();

		std::vector<Vector3r> vertices;

		{
			rational diagonal = rational(5) / 7;

			vertices.push_back(position + Vector3r(0, 0, extends.z));
			vertices.push_back(position + Vector3r(extends.x * diagonal, 0, extends.z * diagonal));
			vertices.push_back(position + Vector3r(extends.x, 0, 0));
			vertices.push_back(position + Vector3r(extends.x * diagonal, 0, -extends.z * diagonal));
			vertices.push_back(position + Vector3r(0, 0, -extends.z));
			vertices.push_back(position + Vector3r(-extends.x * diagonal, 0, -extends.z * diagonal));
			vertices.push_back(position + Vector3r(-extends.x, 0, 0));
			vertices.push_back(position + Vector3r(-extends.x * diagonal, 0, extends.z * diagonal));
		}

		Vector3r up = Vector3r(0, extends.y, 0);

		BSPFace face;

		{
			face.m_Vertices.clear();

			for (int i = 0; i < vertices.size(); i++) {
				face.m_Vertices.push_back(vertices[i] + up);
			}
			face.m_Plane = Planer(Triangle3r(face.m_Vertices[0], face.m_Vertices[1], face.m_Vertices[2]));

			bsp->insert(face, "Cylinder top Plane");
		}

		{
			face.m_Vertices.clear();

			for (int i = vertices.size() - 1; i > 0; i--) {
				face.m_Vertices.push_back(vertices[i] - up);
			}
			face.m_Plane = Planer(Triangle3r(face.m_Vertices[0], face.m_Vertices[1], face.m_Vertices[2]));

			bsp->insert(face, "Cylinder bottom Plane");
		}
		
		auto makeFace = [&](const Vector3r &a, const Vector3r &b, const Vector3r &c, const Vector3r &d) {
			face.m_Vertices.clear();

			face.m_Vertices.push_back(a);
			face.m_Vertices.push_back(b);
			face.m_Vertices.push_back(c);
			face.m_Vertices.push_back(d);

			face.m_Plane = Planer(Triangle3r(a, b, c));

			if (BSP_DEBUG) {
				auto d1 = face.m_Plane.distanceFrom(a);
				auto d2 = face.m_Plane.distanceFrom(b);
				auto d3 = face.m_Plane.distanceFrom(c);
				auto d4 = face.m_Plane.distanceFrom(d);

				if (d1 != 0) {
					LOG("Invalid distance from plane (d1) : " << d1);
					assert(false);
				}
				if (d2 != 0) {
					LOG("Invalid distance from plane (d2) : " << d2);
					assert(false);
				}
				if (d3 != 0) {
					LOG("Invalid distance from plane (d3) : " << d3);
					assert(false);
				}
				if (d4 != 0) {
					LOG("Invalid distance from plane (d4) : " << d4);
					assert(false);
				}
			}
		};

		for (int i = 0; i < vertices.size(); i++)
		{
			int index1 = i;
			int index2 = (i + 1) % vertices.size();


			makeFace(
				vertices[index2] + up,
				vertices[index1] + up,
				vertices[index1] - up,
				vertices[index2] - up);

			bsp->insert(face, "Side Plane");
		}

		return std::move(bsp);
	}
	std::unique_ptr<BSP3> makeSphere(const Vector3r & position, const Vector3r extends)
	{
		auto bsp = std::make_unique<BSP3>();

		std::vector<Vector3r> middleRing;
		std::vector<Vector3r> innerRing;

		Vector3r up = Vector3r(0, extends.y, 0);

		rational diagonal = rational(5) / 7;
		Vector3r innerUp = Vector3r(0, extends.y * diagonal, 0);

		//Calculate middle ring vertices
		{
			rational x = extends.x;
			rational z = extends.z;

			middleRing.push_back(position + Vector3r(0, 0, z));
			middleRing.push_back(position + Vector3r(x * diagonal, 0, z * diagonal));
			middleRing.push_back(position + Vector3r(x, 0, 0));
			middleRing.push_back(position + Vector3r(x * diagonal, 0, -z * diagonal));
			middleRing.push_back(position + Vector3r(0, 0, -extends.z));
			middleRing.push_back(position + Vector3r(-x * diagonal, 0, -z * diagonal));
			middleRing.push_back(position + Vector3r(-x, 0, 0));
			middleRing.push_back(position + Vector3r(-x * diagonal, 0, z * diagonal));
		}

		//Calculate inner ring vertices
		{
			rational x = extends.x;
			rational z = extends.z;

			innerRing.push_back(position + Vector3r(0, 0, z) * diagonal);
			innerRing.push_back(position + Vector3r(x * diagonal, 0, z * diagonal) * diagonal);
			innerRing.push_back(position + Vector3r(x, 0, 0)* diagonal);
			innerRing.push_back(position + Vector3r(x * diagonal, 0, -z * diagonal)* diagonal);
			innerRing.push_back(position + Vector3r(0, 0, -extends.z)* diagonal);
			innerRing.push_back(position + Vector3r(-x * diagonal, 0, -z * diagonal)* diagonal);
			innerRing.push_back(position + Vector3r(-x, 0, 0)* diagonal);
			innerRing.push_back(position + Vector3r(-x * diagonal, 0, z * diagonal)* diagonal);
		}

		BSPFace face;

		auto makeFace4 = [&](const Vector3r &a, const Vector3r &b, const Vector3r &c, const Vector3r &d) {
			face.m_Vertices.clear();

			face.m_Vertices.push_back(a);
			face.m_Vertices.push_back(b);
			face.m_Vertices.push_back(c);
			face.m_Vertices.push_back(d);

			face.m_Plane = Planer(Triangle3r(a, b, c));

			if (BSP_DEBUG) {
				auto d1 = face.m_Plane.distanceFrom(a);
				auto d2 = face.m_Plane.distanceFrom(b);
				auto d3 = face.m_Plane.distanceFrom(c);
				auto d4 = face.m_Plane.distanceFrom(d);

				if (d1 != 0) {
					LOG("Invalid distance from plane (d1) : " << d1);
					assert(false);
				}
				if (d2 != 0) {
					LOG("Invalid distance from plane (d2) : " << d2);
					assert(false);
				}
				if (d3 != 0) {
					LOG("Invalid distance from plane (d3) : " << d3);
					assert(false);
				}
				if (d4 != 0) {
					LOG("Invalid distance from plane (d4) : " << d4);
					assert(false);
				}
			}
		};
		auto makeFace3 = [&](const Vector3r &a, const Vector3r &b, const Vector3r &c) {
			face.m_Vertices.clear();

			face.m_Vertices.push_back(a);
			face.m_Vertices.push_back(b);
			face.m_Vertices.push_back(c);

			face.m_Plane = Planer(Triangle3r(a, b, c));

			if (BSP_DEBUG) {
				auto d1 = face.m_Plane.distanceFrom(a);
				auto d2 = face.m_Plane.distanceFrom(b);
				auto d3 = face.m_Plane.distanceFrom(c);

				if (d1 != 0) {
					LOG("Invalid distance from plane (d1) : " << d1);
					assert(false);
				}
				if (d2 != 0) {
					LOG("Invalid distance from plane (d2) : " << d2);
					assert(false);
				}
				if (d3 != 0) {
					LOG("Invalid distance from plane (d3) : " << d3);
					assert(false);
				}
			}
		};

		//Make simple faces
		{
			for (int i = 0; i < middleRing.size(); i++)
			{
				int index1 = i;
				int index2 = (i + 1) % middleRing.size();

				makeFace4(
					middleRing[index1],
					middleRing[index2],
					innerRing[index1] + innerUp,
					innerRing[index2] + innerUp);

				bsp->insert(face, "Middle To Upper");

				makeFace4(
					middleRing[index2],
					middleRing[index1],
					innerRing[index1] - innerUp,
					innerRing[index2] - innerUp);

				bsp->insert(face, "Middle To Lower");
			}
		}

		//Making the rest
		{
			for (int i = 0; i < middleRing.size(); i++)
			{
				int index1 = i;
				int index2 = (i + 1) % middleRing.size();

				makeFace3(
					up + position,
					innerRing[index1] + innerUp,
					innerRing[index2] + innerUp);

				bsp->insert(face, "Upper to top");

				makeFace3(
					-up + position,
					innerRing[index2] - innerUp,
					innerRing[index1] - innerUp);

				bsp->insert(face, "Lower to bottom");
			}
		}
		
		return std::move(bsp);
	}
#endif
}