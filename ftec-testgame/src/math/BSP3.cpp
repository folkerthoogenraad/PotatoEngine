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

	bool BSPNode3::valid() const
	{
		BSPFace face = m_BSP->getPlane(m_Index);

		if (face.m_Plane.direction.sqrmagnitude() == 0)
			return false;

		for (const auto &v : m_Vertices) {
			if (!face.m_Plane.distanceFrom(v) == 0)
				return false;
		}

		return true;
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

		return (BSPDirection)s;
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

	std::shared_ptr<BSPNode3> BSPNode3::clone(BSP3 *newBSP) const
	{
		auto res = std::make_shared<BSPNode3>(*this);

		res->m_BSP = newBSP;
		if (res->m_Front) {
			res->m_Front = m_Front->clone(newBSP);
			res->m_Front->m_Parent = res.get();
		}
		if (res->m_Back) {
			res->m_Back = m_Back->clone(newBSP);
			res->m_Back->m_Parent = res.get();
		}

		return std::move(res);
	}

	bool BSPNode3::isSpace() const
	{
		return m_Front == nullptr;
	}

	bool BSPNode3::insert(std::shared_ptr<BSPNode3> node, bool allowFront, bool allowBack) //TODO allow front and allow back stuff
	{
		assert(node->m_Vertices.size() >= 3);

		const BSPFace &face = m_BSP->getPlane(m_Index);
		const BSPFace &otherFace = m_BSP->getPlane(node->m_Index);

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

			if (dir == BSPDirection::ON && index != node->m_Vertices.size())
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

			if (index != node->m_Vertices.size())
				directions.push_back(dir);
			previous = dir;
		}

		assert(intersectionIndices.size() <= 2);

		//Generate intersection points
		for (int i = 0; i < intersectionIndices.size(); i++){
			int index1 = (intersectionIndices[i] - 1);
			int index2 = (intersectionIndices[i]);

			while (index1 < 0)
				index1 += node->m_Vertices.size();
			while (index1 >= node->m_Vertices.size())
				index1 -= node->m_Vertices.size();

			while (index2 < 0)
				index2 += node->m_Vertices.size();
			while (index2 >= node->m_Vertices.size())
				index2 -= node->m_Vertices.size();

			auto res = intersect(face.m_Plane, Line3r(node->m_Vertices[index1], node->m_Vertices[index2]));
			
			assert(res.collided);

			intersectionPoints.push_back(*res);
		}

		assert(intersectionIndices.size() == intersectionPoints.size());

		//Create put function
		auto put = [&](std::shared_ptr<BSPNode3> &target, std::shared_ptr<BSPNode3> &source, bool allowed) {
			if (target) {
				target->insert(source, allowFront, allowBack);
			}
			else if (allowed || face.m_ID == otherFace.m_ID) {
				target = source;
				target->m_Parent = this;
				target->m_BSP = m_BSP;
			}
		};

		//-------------------------------------------------------------------
		// Insert in the back
		//-------------------------------------------------------------------
		if (hasBack && !hasFront) {
			put(m_Back, node, allowBack);
		}

		//-------------------------------------------------------------------
		// Insert in the front
		//-------------------------------------------------------------------
		else if (hasFront && !hasBack) {
			put(m_Front, node, allowFront);
		}

		//-------------------------------------------------------------------
		// Split the polygon
		//-------------------------------------------------------------------
		else if (hasBack && hasFront) {
			//Split the polygon.
			assert(onCount <= 2);
			assert(intersectionPoints.size() + onCount == 2);

			auto findNext = [&](BSPDirection dir, int offset) -> int {
				for (int i = offset; i < directions.size() + offset; i++) {
					int index = i % directions.size();
					if (directions[index] == dir)
						return index;
				}
				assert(false);
				return -1;
			};
			auto split = [&](std::shared_ptr<BSPNode3> &newNode, BSPDirection front, BSPDirection back) {
				//Calculate front
				int startIndex = findNext(front, 0);
				int index = startIndex;
				bool done = false;

				auto addIndex = [&index, &directions]() { index++; index = index % directions.size(); };

				while (!done) {
					newNode->m_Vertices.push_back(node->m_Vertices[index]);

					bool isOn = directions[index] == BSPDirection::ON;

					addIndex();

					//Ayy we found an intersection
					if (directions[index] == back) {
						if (!isOn) {
							int intersectionIndex = -1;

							//Find the intersection index
							for (int i = 0; i < intersectionIndices.size(); i++) {
								if (intersectionIndices[i] == index)
									intersectionIndex = i;
							}

							//Assert that we found it, very improtant
							assert(intersectionIndex >= 0);

							//Insert the vertex into the right position
							newNode->m_Vertices.push_back(intersectionPoints[intersectionIndex]);
						}

						while (directions[index] == back) {
							addIndex();
						}

						if (directions[index] == front) {
							int intersectionIndex = -1;

							//Find the intersection index
							for (int i = 0; i < intersectionIndices.size(); i++) {
								if (intersectionIndices[i] == index)
									intersectionIndex = i;
							}

							//Assert that we found it, very improtant
							assert(intersectionIndex >= 0);

							//Insert the vertex into the right position
							newNode->m_Vertices.push_back(intersectionPoints[intersectionIndex]);
						}
					}

					if (index == startIndex)
						done = true;
				}
			};

			{
				auto front = std::make_shared<BSPNode3>();
				front->m_BSP = m_BSP;
				front->m_Index = node->m_Index;

				split(front, BSPDirection::FRONT, BSPDirection::BACK);
				put(m_Front, front, allowFront);
			}

			{
				auto back = std::make_shared<BSPNode3>();
				back->m_BSP = m_BSP;
				back->m_Index = node->m_Index;

				split(back, BSPDirection::BACK, BSPDirection::FRONT);
				put(m_Back, back, allowBack);
			}
		}

		//-------------------------------------------------------------------
		// Coplaner panic
		//-------------------------------------------------------------------
		else { //Oh my, we are coplanar. Panic!
			//assert(false);
			LOG("Coplaner, may result in bugs.");
		}

		return false;
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
	
	void BSPNode3::testFace(const BSPFace & plane, const BSPNode3 &node, int & frontCount, int & backCount)
	{
		auto insertTest = [&plane](const Vector3r &point) -> rational {
			auto r = plane.m_Plane.distanceFrom(point);
			return std::move(r);
		};
		auto compare = [&frontCount, &backCount](const rational &v) {
			int s = v.sign();

			if (s > 0)
				frontCount++;
			else if (s < 0)
				backCount++;
		};

		//Test the triangle
		for (const auto &v : node.m_Vertices)
		{
			//We calculate the full distance stuff, however, we only use the sign
			//We might be able to reduce this a bit.

			//if (frontCount > 0 && backCount > 0)
			//	break;

			compare(insertTest(v));
		}

	}

	//Removes everything inside the BSP
	bool BSPNode3::clip(const BSP3 & bsp)
	{
		if (m_Front && m_Front->clip(bsp))
			m_Front.reset();

		if (m_Back && m_Back->clip(bsp))
			m_Back.reset();

		if (!m_Front && !m_Back) {
			BSPFace &self = m_BSP->m_Planes[m_Index];
			
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
						testFace(other, *this, frontCount, backCount);
					}
					if (dir == -1){
						testFace(other, *this, backCount, frontCount);
					}

					if (backCount > 0) {
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

			return !done;
		}

		return false;
	}
#if 0
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
#endif

	void BSP3::insert(std::vector<Vector3r> verts, const std::string & dbg, bool allowFront, bool allowBack, int id)
	{
		assert(verts.size() > 0);
		
		m_Planes.emplace_back();
		BSPFace &face = m_Planes.back();

		face.m_DebugTag = dbg;
		face.m_ID = id;
		face.m_Plane = Planer(verts[0], verts[1], verts[2]);

		auto node = std::make_shared<BSPNode3>();
		node->m_BSP = this;
		node->m_Index = m_Planes.size() - 1;
		node->m_Vertices = std::move(verts);

		node->valid();
		
		if (m_Root)
			m_Root->insert(node, allowFront, allowBack);
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

	std::unique_ptr<BSP3> BSP3::clone() const
	{
		auto bsp = std::make_unique<BSP3>(*this);

		bsp->m_Root = m_Root->clone(bsp.get());

		return std::move(bsp);
	}

	BSP3 & BSP3::csgUnion(const BSP3 & other)
	{
		if (!other.isConvex())
			LOG("Other BSP is not convex!");

		//Recursion not allowed when type is auto
		std::function<void(const std::shared_ptr<BSPNode3> &node)> insertAll = [&](const std::shared_ptr<BSPNode3> &node) -> void {
			//We recreate the plane here
			//If this is a rational with verts, 
			//this can be very costly.
			//We are able to reduce this cost by just copying the planes from the old BSP
			//TODO make that

			std::vector<Vector3r> verts = node->m_Vertices;

			insert(verts, node->m_BSP->getPlane(node->m_Index).m_DebugTag, false, true, 1);

			if (node->m_Front)
				insertAll(node->m_Front);
			if (node->m_Back)
				insertAll(node->m_Back);

		};

		if (m_Root && other.m_Root)
			insertAll(other.m_Root);

		resetID();

		return *this;
	}

#if 0
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
#endif
	BSP3 & BSP3::csgDifference(const BSP3 & other)
	{
		if (!other.isConvex())
			LOG("Other BSP is not convex!");

		if (m_Root->clip(other)) {
			m_Root = nullptr;
		}
		
		//Recursion not allowed when type is auto
		std::function<void(const std::shared_ptr<BSPNode3> &node)> insertAll = [&](const std::shared_ptr<BSPNode3> &node) -> void{
			//We recreate the plane here
			//If this is a rational with verts, 
			//this can be very costly.
			//We are able to reduce this cost by just copying the planes from the old BSP
			//TODO make that

			std::vector<Vector3r> verts = node->m_Vertices;
			std::reverse(verts.begin(), verts.end());

			insert(verts, node->m_BSP->getPlane(node->m_Index).m_DebugTag, true, false, 1);

			if (node->m_Front)
				insertAll(node->m_Front);
			if (node->m_Back)
				insertAll(node->m_Back);

		};

		if(m_Root && other.m_Root)
			insertAll(other.m_Root);
		
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

		Vector3r extra(0, 0, extends.z);

		bsp->insert({ a, b, c, d }, "Bottom", true, false);

		bsp->insert({ e, h, g, f }, "Top", true, false);

		bsp->insert({ a, e, f, b }, "Front", true, false);

		bsp->insert({ c, g, h, d }, "Back", true, false);
		
		bsp->insert({ b, f, g, c}, "Left", true, false);

		bsp->insert({ a, d, h, e }, "Right", true, false);

		return std::move(bsp);
	}

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
			std::vector<Vector3r> verts;

			for (int i = 0; i < vertices.size(); i++) {
				verts.push_back(vertices[i] + up);
			}

			bsp->insert(verts, "Cylinder top Plane", true, false);
		}

		{
			std::vector<Vector3r> verts;

			for (int i = vertices.size() - 1; i >= 0; i--) {
				verts.push_back(vertices[i] - up);
			}

			bsp->insert(verts, "Cylinder bottom Plane", true, false);
		}
		
		for (int i = 0; i < vertices.size(); i++)
		{
			int index1 = i;
			int index2 = (i + 1) % vertices.size();


			bsp->insert({
				vertices[index2] + up,
				vertices[index1] + up,
				vertices[index1] - up,
				vertices[index2] - up
			}, "Side Plane", true, false);
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

		//Make simple faces
		{
			for (int i = 0; i < middleRing.size(); i++)
			{
				int index1 = i;
				int index2 = (i + 1) % middleRing.size();

				bsp->insert({
					middleRing[index1],
					middleRing[index2] ,
					innerRing[index2] + innerUp,
					innerRing[index1] + innerUp
				}, "Middle to Upper");

				bsp->insert({
					middleRing[index1],
					innerRing[index1] - innerUp ,
					innerRing[index2] - innerUp,
					middleRing[index2]
				}, "Middle to Lower");
			}
		}

		//Making the rest
		{
			for (int i = 0; i < middleRing.size(); i++)
			{
				int index1 = i;
				int index2 = (i + 1) % middleRing.size();

				bsp->insert({
					up + position,
					innerRing[index1] + innerUp,
					innerRing[index2] + innerUp}, "Upper to top");

				bsp->insert({
					-up + position,
					innerRing[index2] - innerUp,
					innerRing[index1] - innerUp }, "Lower to bottom");
			}
		}
		
		return std::move(bsp);
	}
}