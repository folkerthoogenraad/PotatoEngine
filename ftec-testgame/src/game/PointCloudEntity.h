#pragma once

#include "scene/Entity.h"
#include "math/vec3.h"
#include "math/lego3.h"
#include <vector>
#include <memory>

namespace ftec {

	class PBRMaterial;
	class Mesh;

	class PointCloudEntity : public Entity {
		std::vector<vec3f> m_Points;
		std::shared_ptr<PBRMaterial> m_Material;
		std::unique_ptr<Mesh> m_Mesh;
		vec3f m_Direction;
		float m_Time;
		bool m_Render;

		vec3f center;
		float speed;
		float amount;
		float away = 0.25f;
	public:
		PointCloudEntity(const lego3f &);
		~PointCloudEntity() = default;
		void update() override;
		void render() override;
	};
}