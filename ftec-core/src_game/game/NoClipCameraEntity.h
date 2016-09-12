#pragma once
#include "scene/Entity.h"

namespace ftec {
	class NoClipCameraEntity : public Entity {
	public:
		NoClipCameraEntity();
		~NoClipCameraEntity();
		void update() override;
		void render() override;
	};
}