#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "graphics/Camera.h"

namespace ftec {
	class Scene {
	public:
		Camera m_Camera;

	public:
		std::vector<std::shared_ptr<Entity>> entities;
	public:
		Scene();
		virtual ~Scene() = default;

		virtual void update();
		virtual void render();

		void addEntity(std::shared_ptr<Entity> entity);
		void removeEntity(std::shared_ptr<Entity> entity);
	};

}