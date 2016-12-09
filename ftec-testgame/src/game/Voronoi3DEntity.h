#pragma once
#include "scene/Entity.h"
#include <vector>
#include "math/Vector3.h"

namespace ftec {
	class Voronoi3DEntity : public Entity {
	private:
		std::vector<Vector3d> m_Points;
		void create();
	public:
		Voronoi3DEntity();
		~Voronoi3DEntity() = default;
		void update() override;
		void render() override;
	};
}