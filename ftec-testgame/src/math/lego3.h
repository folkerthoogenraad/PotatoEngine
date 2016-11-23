#pragma once

#include "math/vec3.h"
#include "math/plane.h"

#include "logger/log.h"
#include <vector>

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

					line3f line = i->intersection(*j);

					if (line.sqrmagnitude() == 0)
						continue;

					if (line.a.x != line.a.x)
						continue;

					for (auto k = j; k != planes.end(); k++) {
						if (k == i || k == j)
							continue;

						vec3<T> result = k->intersection(line);

						if (result.x != result.x)
							continue;

						m_Vertices.push_back(std::move(result));
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
					[&p](vec3f &v) -> bool {
					return p.distanceFrom(v) < -0.001; //Small rounding error fix?
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