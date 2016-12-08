#pragma once

#include "scene/Entity.h"
#include "math/vec3.h"
#include "math/lego3.h"

#include "math/Delaunay3.h"

#include <vector>
#include <memory>

namespace ftec {

	struct PBRMaterial;
	class Mesh;

	class PointCloudEntity : public Entity {
		std::vector<vec3d> m_Points;
		std::shared_ptr<PBRMaterial> m_Material;
		std::unique_ptr<Mesh> m_Mesh;
		Delaunay3d del;
		vec3d m_Direction;
		float m_Time;
		bool m_Render;

		vec3d center;
		float speed;
		float amount;
		float away = 0.25f;
	public:
		PointCloudEntity(std::vector<vec3d> vertices);
		~PointCloudEntity() = default;
		void update() override;
		void render() override;
	};
}