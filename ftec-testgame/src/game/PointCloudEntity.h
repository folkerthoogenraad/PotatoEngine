#pragma once

#include "scene/Entity.h"
#include "math/Vector3.h"
#include "math/lego3.h"

#include "math/Delaunay3.h"

#include <vector>
#include <memory>

namespace ftec {

	struct PBRMaterial;
	class Mesh;

	class PointCloudEntity : public Entity {
		std::vector<Vector3d> m_Points;
		std::shared_ptr<PBRMaterial> m_Material;
		std::unique_ptr<Mesh> m_Mesh;
		Delaunay3d del;
		Vector3d m_DiRectangleion;
		float m_Time;
		bool m_Render;

		Vector3d center;
		float speed;
		float amount;
		float away = 0.25f;

		Vector3f m_Position;
	public:
		PointCloudEntity(std::shared_ptr<EngineContext> context, std::vector<Vector3d> vertices);
		~PointCloudEntity() = default;
		void update() override;

		void render() override;
	};
}