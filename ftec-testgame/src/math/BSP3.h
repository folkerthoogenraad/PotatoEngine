#pragma once

#include "math/Triangle3.h"
#include "math/Vector3.h"
#include "math/Plane.h"

#include <vector>
#include <memory>

namespace ftec {

	template <typename T>
	class BSP3;

	template <typename T>
	struct CachedTriangle {
		Triangle3<T> m_Triangle;
		Vector3<T> m_Normal;
	};

	//This can really benefit from more tight packing and inline nodes (unlike these nodes)
	//This can be shared between BSP2 and BSP3, but whatever
	struct BSPNode3 {
		std::shared_ptr<BSPNode3> m_Front;	//8 bytes
		std::shared_ptr<BSPNode3> m_Back;	//8 bytes

		BSPNode3 *m_Parent;					//8 bytes

		size_t m_Index;						//8 bytes

	public:
		template <typename T>
		void insert(BSP3<T> &bsp, size_t index)
		{
			CachedTriangle<T> &self = bsp.m_Triangles[m_Index];
			CachedTriangle<T> &other = bsp.m_Triangles[index];

			int frontCount = 0;
			int backCount = 0;
			
			auto insertTest = [&self](const Vector3<T> &point) -> T{
				return Vector3<T>::dot(self.m_Normal, point - self.m_Triangle.a);
			};
			auto compare = [&frontCount, &backCount](const T &v) {
				if (v > 0)
					frontCount++;
				else if (v < 0)
					backCount++;
			};

			//Test the triangle
			compare(insertTest(other.m_Triangle.a));
			compare(insertTest(other.m_Triangle.b));
			compare(insertTest(other.m_Triangle.c));
			
			auto create = [&bsp, &index, this](std::shared_ptr<BSPNode3> &position) {
				if (position) {
					position->insert(bsp, index);
				}
				else {
					position = std::make_shared<BSPNode3>();
					position->m_Parent = this;
					position->m_Index = index;
				}
			};

			if (frontCount == 0 && backCount == 0) {
				//TODO handle this case
				//Look at a few things, like the normal direction might be important?
				assert(false);
			}
			if (frontCount > 0){
				create(m_Front);
			}
			if (backCount > 0) {
				create(m_Back);
			}
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
		std::vector<CachedTriangle<T>> m_Triangles;
		std::shared_ptr<BSPNode3> m_Root;
	
	public:

		void insert(Triangle3<T> triangle)
		{
			CachedTriangle<T> ct = {
				std::move(triangle)
			};
			ct.m_Normal = ct.m_Triangle.normal();
			m_Triangles.push_back(std::move(ct));

			if (!m_Root) {
				m_Root = std::make_shared<BSPNode3>();
				m_Root->m_Index = 0;
			}
			else {
				m_Root->insert(*this, m_Triangles.size() - 1);
			}
		}
		int cellcount()
		{
			return m_Root ? m_Root->cellcount() : 0;
		}

		friend BSPNode3;
	};

}