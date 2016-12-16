#include "CollisionWorld.h"
#include "CollisionTransform.h"

#include "logger/log.h"

namespace ftec {

	CollisionWorld::~CollisionWorld()
	{
		if (m_Colliders.size() > 0){
			//Please, it should be build that this is never needed.
			LOG_DEBUG("WARNING, possible memory leak. " << m_Colliders.size() << " colliders left in collision world uppon collision world destruction. ");
		}
	}

	void CollisionWorld::addTransform(CollisionTransform * collider)
	{
		m_Colliders.push_back(collider);
	}

	void CollisionWorld::removeTransform(CollisionTransform * collider)
	{
		auto i = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
		
		if (i != m_Colliders.end())
			m_Colliders.erase(i);
	}
}
