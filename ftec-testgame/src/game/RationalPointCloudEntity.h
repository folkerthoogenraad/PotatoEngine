#pragma once

#include "scene/Entity.h"
#include "math/Vector3.h"
#include "math/Rational.h"

#include "math/Delaunay3.h"

#include <vector>
#include <memory>

namespace ftec {

	struct PBRMaterial;
	class Mesh;

	class RationalPointCloudEntity : public Entity {
		std::shared_ptr<PBRMaterial> m_Material;
		std::unique_ptr<Mesh> m_Mesh;
		Delaunay3<rational> del;

		Vector3f m_Position;
	public:
		RationalPointCloudEntity(const std::vector<Vector3r> &vertices);
		~RationalPointCloudEntity() = default;

		void render() override;
	};
}