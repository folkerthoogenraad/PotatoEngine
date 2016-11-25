#pragma once

#include "math/vec3.h"
#include "math/line3.h"
#include "math/plane.h"

#include "math/epsilon.h"
#include "math/collision.h"


#include <vector>
#include <algorithm>

namespace ftec {

	template <typename T>
	class lego3 {
		vec3<T> m_Center;
	public:
		//The vertices generated
		std::vector<vec3<T>> m_Vertices;

		//Recalculates the vertices
		void create(std::vector<plane<T>> planes)
		{
			m_Vertices.clear();

			//Generate all the possible points
			for (auto i = planes.begin(); i != planes.end(); i++) {
				for (auto j = i; j != planes.end(); j++) {
					if (i == j)
						continue;

					auto line = intersect(*i, *j);

					if (!line)
						continue;

					for (auto k = j; k != planes.end(); k++) {
						if (k == i || k == j)
							continue;

						auto point = intersect(*k, *line);

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
					[&p](vec3<T> &v) -> bool {
					return p.distanceFrom(v) < -EPSILON; //Small rounding error fix?
				}), m_Vertices.end());
			}
		}


		void setCenter(vec3<T> center)
		{
			m_Center = center;
		}
		const vec3<T> &getCenter() const { return m_Center; }
	};

	typedef lego3<float> lego3f;
	typedef lego3<double> lego3d;
	typedef lego3<int> lego3i;

}