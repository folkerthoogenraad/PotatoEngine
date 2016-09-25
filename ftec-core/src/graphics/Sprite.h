#pragma once

#include <memory>
#include "math/rect.h"

namespace ftec {
	class Texture;

	class Sprite {
		std::shared_ptr<Texture> m_Texture;
		rect2f m_TextureRectangle;
		rect2f m_UVRectangle;
	public:
		Sprite(std::shared_ptr<Texture> texture);
		Sprite(std::shared_ptr<Texture> texture, const rect2f &rectangle);
		~Sprite() = default;
	protected:
		void recalculateUVRectangle();
	};
}