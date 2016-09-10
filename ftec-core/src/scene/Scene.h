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
		static std::shared_ptr<Scene> currentScene;
	public:
		std::vector<std::shared_ptr<Entity>> entities;
	public:
		Scene();
		virtual ~Scene() = default;

		static inline std::shared_ptr<Scene> getCurrent() { return currentScene; };
		static inline void setCurrent(std::shared_ptr<Scene> scene) { currentScene = scene; };

		virtual void update();
		virtual void render();

		void addEntity(std::shared_ptr<Entity> entity);
		void removeEntity(std::shared_ptr<Entity> entity);
	};

}