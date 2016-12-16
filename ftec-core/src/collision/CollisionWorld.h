#pragma once

#include <memory>
#include <vector>

namespace ftec {

	class CollisionTransform;

	class CollisionWorld {
		//This can be optimized a lot
		std::vector<CollisionTransform*> m_Colliders;
	public:
		~CollisionWorld();

	private:
		void addTransform(CollisionTransform *collider);
		void removeTransform(CollisionTransform *collider);

		friend CollisionTransform;
	};
}