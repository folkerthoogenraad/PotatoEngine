#pragma once

#include "math/Vector3.h"
#include "math/Rectangle.h"


//TODO allow for more interesting shapes that just fucking AABB bounding boxes
namespace ftec {

	class CollisionWorld;

	class CollisionTransform {
	private:
		CollisionWorld *m_World;
	public:
		Rectanglef m_Rectangle;

		bool m_Static;
		int m_Layer;
	public:
		CollisionTransform(Rectanglef rectangle, CollisionWorld *world = nullptr, bool isStatic = false, int layer = -1);
		~CollisionTransform();

		inline const Rectanglef &getAABB(){ return m_Rectangle; };
		
		CollisionWorld *getWorld();
		void setWorld(CollisionWorld *world);
	};
}