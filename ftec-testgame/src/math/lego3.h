#pragma once

#include "math/Vector3.h"
#include "math/Line3.h"
#include "math/Plane.h"

#include "math/epsilon.h"
#include "math/collision.h"


#include <vector>
#include <algorithm>

namespace ftec {

	template <typename T>
	class lego3 {
		Vector3<T> m_Center;
	public:
		//The vertices generated
		std::vector<Vector3<T>> m_Vertices;

		//Recalculates the vertices
		void create(std::vector<Plane<T>> planes)
		{
			m_Vertices.clear();

			//Generate all the possible points
			for (int i = 0; i < planes.size(); i++) {
				for (int j = i + 1; j < planes.size(); j++) {

					auto line = intersect(planes[i], planes[j]);

					if (!line)
						continue;

					for (int k = j + 1; k < planes.size(); k++) {

						auto point = intersect(planes[k], *line);

						if (!point)
							continue;

						m_Vertices.push_back(std::move(point.result));
					}
				}
			}
		
			if (m_Vertices.size() == 0)
				return;

			//Corretly orient the planes inside
			for (auto &p : planes) {
				if (p.distanceFrom(m_Center) < 0) {
					p.flip();
				}
				
				m_Vertices.erase(std::remove_if(m_Vertices.begin(), m_Vertices.end(),
					[&p](Vector3<T> &v) -> bool {
					return p.distanceFrom(v) < -EPSILON; //Small rounding error fix?
				}), m_Vertices.end());
			}
		}


		void setCenter(Vector3<T> center)
		{
			m_Center = center;
		}
		const Vector3<T> &getCenter() const { return m_Center; }
	};

	typedef lego3<float> lego3f;
	typedef lego3<double> lego3d;
	typedef lego3<int> lego3i;

}