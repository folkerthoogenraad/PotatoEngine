#pragma once

#include <memory>
#include <vector>

#include "scene/Entity.h"
#include "terrain/Terrain.h"


namespace ftec {

	class Mesh;

	class RazuraWorldEntity : public Entity {
		std::unique_ptr<Terrain> m_Terrain;
	public:
		virtual void onStart();
		virtual void onEnd();

		void remake();

		virtual void update();
		virtual void render();
	};

}