#include "CollisionTransform.h"
#include "CollisionWorld.h"

namespace ftec {
	CollisionTransform::CollisionTransform(Rectanglef rectangle, CollisionWorld *world, bool isStatic, int layer)
		:m_World(nullptr), m_Rectangle(rectangle), m_Static(isStatic), m_Layer(layer)
	{
		setWorld(m_World);
	}

	CollisionTransform::~CollisionTransform()
	{
		setWorld(nullptr);
	}

	CollisionWorld * CollisionTransform::getWorld()
	{
		return m_World;
	}

	void CollisionTransform::setWorld(CollisionWorld * world)
	{
		if (m_World)
			m_World->removeTransform(this);
		
		m_World = world;

		if (m_World)
			m_World->addTransform(this);
	}


}
