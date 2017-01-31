#include "BSP3.h"

#include "math/collision.h"
#include "math/Ray3.h"

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

	int BSPNode3::cellcount()
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

	int BSPNode3::solidcount()
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

	void BSPNode3::forEach(std::function<void(BSPNode3*)> &func)
	{
		if (m_Front == nullptr)
			func(this);
		else
			m_Front->forEach(func);
		
		if (m_Back != nullptr)
			m_Back->forEach(func);
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

					if (s != (int)indicesAndDirection[i].direction) {
						return true;
					}
				}
				return false;
			
			}), cell.m_Intersections.end());
		}

		//And then return the result
		return std::move(cell);
	}

	bool BSPNode3::isSpace()
	{
		return m_Front == nullptr;
	}

	bool BSPNode3::insert(size_t index, bool allowFront, bool allowBack)
	{
		BSPFace &self = m_BSP->m_Planes[m_Index];
		BSPFace &other = m_BSP->m_Planes[index];

		int frontCount = 0;
		int backCount = 0;

		auto insertTest = [&self](const Vector3r &point) -> rational {
			return self.m_Plane.distanceFrom(point);
		};
		auto compare = [&frontCount, &backCount](const rational &v) {
			int s = v.sign();

			if (s > 0)
				frontCount++;
			else if (s < 0)
				backCount++;
		};

		//Test the triangle
		for (const auto &v : other.m_Vertices)
		{
			//We calculate the full distance stuff, however, we only use the sign
			//We might be able to reduce this a bit.

			if (frontCount > 0 && backCount > 0)
				break;

			compare(insertTest(v));
		}

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
	bool BSPNode3::removeWithoutId(int id)
	{
		BSPFace &self = m_BSP->m_Planes[m_Index];

		if (self.m_ID == id)
			return false;

		if (m_Front) {
			if (m_Front->removeWithoutId(id)) {
				m_Front.reset();
			}
		}

		if (m_Back) {
			if (m_Back->removeWithoutId(id)) {
				m_Back.reset();
			}
		}

		if (!m_Front && !m_Back)
			return true;

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
	int BSP3::cellcount()
	{
		return m_Root ? m_Root->cellcount() : 0;
	}
	int BSP3::solidcount()
	{
		if (m_Root)
			return m_Root->solidcount();
		return 0;
	}
	
	BSP3 & BSP3::csgUnion(const BSP3 & other)
	{
		for (const BSPFace &p : other.m_Planes) {
			insert(p, p.m_DebugTag, 1, false, true);
		}

		resetID();

		return *this;
	}
	BSP3 & BSP3::csgIntersection(const BSP3 & other)
	{
		for (const BSPFace &p : other.m_Planes) {
			insert(p, p.m_DebugTag, 1, true, false);
		}

		resetID();

		return *this;
	}
	BSP3 & BSP3::csgDifference(const BSP3 & other)
	{
		//Keep in mind, we copy here!
		for (BSPFace p : other.m_Planes) {
			p.m_Plane.flip();	
			insert(p, p.m_DebugTag, 1, true, false); //Even better, double copy
		}

		//if (m_Root)
		//	m_Root->removeWithoutId(1);

		resetID();

		return *this;
	}

	void BSP3::forEach(std::function<void(BSPNode3 *)> func)
	{
		if (m_Root)
			m_Root->forEach(func);
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

		BSPFace face;

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

		const Vector3r a(position.x - extends.x, position.y - extends.y, position.z - extends.z);
		const Vector3r b(position.x + extends.x, position.y - extends.y, position.z - extends.z);
		const Vector3r c(position.x + extends.x, position.y - extends.y, position.z + extends.z);
		const Vector3r d(position.x - extends.x, position.y - extends.y, position.z + extends.z);

		const Vector3r e(position.x - extends.x, position.y + extends.y, position.z - extends.z);
		const Vector3r f(position.x + extends.x, position.y + extends.y, position.z - extends.z);
		const Vector3r g(position.x + extends.x, position.y + extends.y, position.z + extends.z);
		const Vector3r h(position.x - extends.x, position.y + extends.y, position.z + extends.z);


		makeFace(a, b, c, d);
		bsp->insert(face, "Bottom");

		makeFace(e, h, g, f);
		bsp->insert(face, "Top");

		makeFace(a, e, f, b);
		bsp->insert(face, "Front");

		makeFace(c, g, h, d);
		bsp->insert(face, "Back");

		makeFace(b, f, g, c);
		bsp->insert(face, "Left");

		makeFace(a, d, h, e);
		bsp->insert(face, "Right");

		return std::move(bsp);
	}
}