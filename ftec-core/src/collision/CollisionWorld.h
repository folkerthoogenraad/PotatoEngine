#pragma once

#include <memory>
#include <vector>

namespace ftec {

	class Collider;

	class CollisionWorld {
		//This can be optimized a lot
		std::vector<Collider*> m_Colliders;
	public:
		~CollisionWorld();

	private:
		void addTransform(Collider *collider);
		void removeTransform(Collider *collider);

		friend Collider;
	};
}