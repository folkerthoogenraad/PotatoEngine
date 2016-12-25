#pragma once

#include <memory>
#include <vector>

#include "scene/Entity.h"

namespace ftec {

	class Mesh;
	struct UnlitMaterial;

	class RazuraWorldEntity : public Entity {
		std::unique_ptr<Mesh> m_Mesh;
		std::unique_ptr<UnlitMaterial> m_Material;
	public:
		RazuraWorldEntity();
		~RazuraWorldEntity();

		virtual void onStart();
		virtual void onEnd();

		virtual void update();
		virtual void render();
	};

}