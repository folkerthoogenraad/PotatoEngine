#pragma once

#include <memory>
#include <vector>

#include "scene/Entity.h"

#include "tiles/Tilemap.h"

namespace ftec {

	class Mesh;
	struct PBRMaterial;

	class RazuraWorldEntity : public Entity {
		Tilemap m_Map;
		std::unique_ptr<Mesh> m_Mesh;
		std::unique_ptr<PBRMaterial> m_Material;
	public:
		RazuraWorldEntity();
		~RazuraWorldEntity();

		virtual void onStart();
		virtual void onEnd();

		virtual void update();
		virtual void render();
	};

}