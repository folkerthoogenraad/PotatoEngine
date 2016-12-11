#pragma once

#include "math/collision.h"
#include "math/sorting.h"

#include <set>

namespace ftec {
	
	template <typename T>
	class lego2{
		Vector2<T> m_Center;
	public:
		//Make these private and make use of constructor?

		//The vertices generated
		std::vector<Vector2<T>> m_Vertices;

		//Recalculates the vertices
		void create(std::vector<Line2<T>> edges)
		{
			//Flip the edges, if needed
			for (Line2<T> &edge : edges) {
				if (edge.distanceFrom(m_Center) < 0) {
					edge.flip();
				}
			}

			//This might not be needed
			std::vector<Vector2<T>> vertices;
			vertices.reserve(edges.size() * edges.size());
			
			m_Vertices.clear();

			//Generate ALL the possible points :')
			for (auto i = edges.begin(); i != edges.end(); ++i) {
				for (auto j = edges.begin(); j != edges.end(); ++j) {
					if (i == j)
						continue;
					
					if (auto res = intersect(*i, *j)) {
						vertices.push_back(res.result);
					}
				}
			}

			//Filter all the stupid edges
			vertices.erase(std::remove_if(vertices.begin(), vertices.end(), 
				[&edges](const Vector2<T> v) {
				for (auto &e : edges) {
					if (e.distanceFrom(v) < -0.05)
						return true;
				}
				return false;
			}), vertices.end());

			//TODO fix that this is not needed
			m_Vertices = vertices;

			polarsort(m_Vertices, m_Center);
		}

		//Makes sure all the lines face the point
		void setCenter(Vector2<T> center) 
		{
			m_Center = center;
		}
		const Vector2<T> &getCenter() { return m_Center; }
	};

	typedef lego2<float> lego2f;
	typedef lego2<double> lego2d;
	typedef lego2<int> lego2i;

}