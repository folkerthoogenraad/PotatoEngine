#pragma once

#include <memory>
#include "graphics/Camera.h"

namespace ftec {
	class Scene {
		Camera camera;
	private:
		static std::unique_ptr<Scene> currentScene;
	public:
		Scene();
		~Scene() = default;

		void update();

		static inline Scene &getCurrent() { return *currentScene; };
		static inline void setCurrent(const Scene &scene) { currentScene = std::make_unique<Scene>(scene); };

	};
}