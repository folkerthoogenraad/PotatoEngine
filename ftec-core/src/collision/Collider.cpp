#include "Collider.h"

#include "CollisionWorld.h"

namespace ftec {
	Collider::Collider(Rectanglef rectangle, Entity *entity, CollisionWorld *world, bool isStatic, int layer)
		:m_Entity(entity), m_World(nullptr), m_Rectangle(std::move(rectangle)), m_Static(isStatic), m_Layer(layer)
	{
		setWorld(m_World);
	}

	Collider::~Collider()
	{
		setWorld(nullptr);
	}

	Entity * Collider::getEntity()
	{
		return m_Entity;
	}

	Collider &Collider::setEntity(Entity * entity)
	{
		m_Entity = entity;
		return *this;
	}

	CollisionWorld * Collider::getWorld()
	{
		return m_World;
	}

	Collider &Collider::setWorld(CollisionWorld * world)
	{
		if (m_World)
			m_World->removeTransform(this);
		
		m_World = world;

		if (m_World)
			m_World->addTransform(this);

		return *this;
	}


}
