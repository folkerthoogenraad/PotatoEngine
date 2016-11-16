#pragma once

#include "math/line.h"
#include "math/vec2.h"
#include <set>

namespace ftec {
	
	template <typename T>
	class lego2{
		vec2<T> m_Center;
	public:
		//Make these private and make use of constructor?
		std::vector<line2<T>> m_Edges;
		std::vector<vec2<T>> m_Vertices;

		//Recalculates the vertices
		void create()
		{
			setCenter(m_Center);

			std::set<vec2<T>> vertices;
#if 0
			std::vector<vec2<T>> vertices;
#endif
			m_Vertices.clear();

			//Generate ALL the possible points :')
			for (auto i = m_Edges.begin(); i != m_Edges.end(); ++i) {
				for (auto j = m_Edges.begin(); j != m_Edges.end(); ++j) {
					if (i == j)
						continue;
					
					if (intersects(*i, *j)) {
						vertices.insert({
							intersection(*i, *j)
						});
#if 0
						vertices.push_back(intersection(*i, *j));
#endif
					}
				}
			}

			//Filter all the stupid edges

			for (auto &e : m_Edges) {
				for (auto i = vertices.begin(); i != vertices.end();) {
					//Yes, rounding errors are THIS bad
					//Should be fixed
					if (e.distanceFrom(*i) < -0.05) {
						 i =vertices.erase(i);
					}
					else {
						++i;
					}
				}
			}

			
#if 0
			vertices.erase(std::remove_if(vertices.begin(), vertices.end(), 
				[this](const vec2<T> v) {
				for (auto &e : m_Edges) {
					return e.distanceFrom(v) < -0.05;
				}
			}), vertices.end());
#endif
			
			for (auto &v : vertices) {
				m_Vertices.push_back(v);
			}

			polarSort(m_Vertices, m_Center);
		}

		//Makes sure all the lines face the point
		void setCenter(vec2<T> center) 
		{
			m_Center = center;
			for (line2<T> &edge : m_Edges) {
				if (edge.distanceFrom(center) < 0) {
					edge.flip();
				}
			}
		}
		const vec2<T> &getCenter() { return m_Center; }
	};

	typedef lego2<float> lego2f;
	typedef lego2<double> lego2d;
	typedef lego2<int> lego2i;

}