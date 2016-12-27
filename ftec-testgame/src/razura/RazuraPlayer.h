#pragma once

#include <memory>

#include "math/Vector3.h"
#include "scene/Entity.h"

namespace ftec {

	class Mesh;
	struct PBRMaterial;

	class RazuraPlayer : public Entity {
		Vector3f m_Position;
		std::unique_ptr<Mesh> m_Mesh;
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