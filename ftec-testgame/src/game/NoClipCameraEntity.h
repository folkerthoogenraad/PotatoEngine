#pragma once
#include "scene/Entity.h"

namespace ftec {
	class NoClipCameraEntity : public Entity {
	private:
		bool m_MouseGrabbed = false;
	public:
		NoClipCameraEntity();
		~NoClipCameraEntity();

		void update() override;
	};
}