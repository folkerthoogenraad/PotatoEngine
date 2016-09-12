#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "graphics/Camera.h"

namespace ftec {
	class Scene {
	public:
		Camera m_Camera;
	private:
		std::vector<std::shared_ptr<Entity>> m_Entities;
	public:
		Scene();
		virtual ~Scene() = default;

		virtual void update();
		virtual void render();

		void addEntity(std::shared_ptr<Entity> entity);
		void removeEntity(std::shared_ptr<Entity> entity);
	};

}