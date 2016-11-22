#pragma once

#include "scene/Entity.h"
#include "math/vec3.h"
#include <vector>
#include <memory>

namespace ftec {

	class PBRMaterial;
	class Mesh;

	class PointCloudEntity : public Entity {
		std::vector<vec3f> m_Points;
		std::shared_ptr<PBRMaterial> m_Material;
		std::unique_ptr<Mesh> m_Mesh;
		float m_Time;

		bool m_Render;
	public:
		PointCloudEntity(std::vector<vec3f> points);
		~PointCloudEntity() = default;
		void update() override;
		void render() override;
	};
}