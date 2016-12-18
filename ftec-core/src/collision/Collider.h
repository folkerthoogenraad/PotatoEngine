#pragma once

#include "math/Vector3.h"
#include "math/Rectangle.h"


//TODO allow for more interesting shapes that just fucking AABB bounding boxes
namespace ftec {

	class CollisionWorld;
	class Entity;

	class Collider {
	private:
		Entity *m_Entity;
		CollisionWorld *m_World;
	public:
		Rectanglef m_Rectangle;

		bool m_Static;
		int m_Layer;
	public:
		Collider(Rectanglef rectangle, Entity *entity = nullptr, CollisionWorld *world = nullptr, bool isStatic = false, int layer = -1);
		~Collider();

		inline const Rectanglef &getAABB(){ return m_Rectangle; };
		
		Entity *getEntity();
		Collider &setEntity(Entity *entity);

		CollisionWorld *getWorld();
		Collider &setWorld(CollisionWorld *world);
	};
}