#pragma once

#include <memory>
#include "scene/Entity.h"

namespace ftec {

	class Mesh;
	struct PBRMaterial;

	class RazuraPlayer : public Entity {
		std::shared_ptr<Mesh> m_Mesh;
		std::unique_ptr<PBRMaterial> m_Material;
	public:
		RazuraPlayer();
		~RazuraPlayer();

		virtual void onStart();
		virtual void onEnd();

		virtual void update();
		virtual void render();
	};
}