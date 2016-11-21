#pragma once

#include "math/collision.h"
#include "math/helpers.h"
#include <set>

namespace ftec {

	template <typename T>
	class lego3 {
		vec3<T> m_Center;
	public:
		//Make these private and make use of constructor?

		//The vertices generated
		std::vector<vec2<T>> m_Vertices;

		//Recalculates the vertices
		void create(std::vector<line2<T>> edges)
		{
			//Flip the edges, if needed
			for (line2<T> &edge : edges) {
				if (edge.distanceFrom(m_Center) < 0) {
					edge.flip();
				}
			}

			//This might not be needed
			std::vector<vec2<T>> vertices;
			vertices.reserve(edges.size() * edges.size());

			m_Vertices.clear();

			//Generate ALL the possible points :')
			for (auto i = edges.begin(); i != edges.end(); ++i) {
				for (auto j = edges.begin(); j != edges.end(); ++j) {
					if (i == j)
						continue;

					if (intersects(*i, *j)) {
						vertices.push_back(intersection(*i, *j));
					}
				}
			}

			//Filter all the stupid edges
			vertices.erase(std::remove_if(vertices.begin(), vertices.end(),
				[&edges](const vec2<T> v) {
				for (auto &e : edges) {
					if (e.distanceFrom(v) < -0.05)
						return true;
				}
				return false;
			}), vertices.end());

			//TODO fix that this is not needed
			m_Vertices = vertices;

			polarSort(m_Vertices, m_Center);
		}

		//Makes sure all the lines face the point
		void setCenter(vec2<T> center)
		{
			m_Center = center;
		}
		const vec2<T> &getCenter() { return m_Center; }
	};

	typedef lego3<float> lego3f;
	typedef lego3<double> lego3d;
	typedef lego3<int> lego3i;

}