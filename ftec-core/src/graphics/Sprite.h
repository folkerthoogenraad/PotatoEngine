#pragma once

#include <memory>
#include "math/rect.h"

namespace ftec {
	class Texture;

	class Sprite {
	public:
		std::shared_ptr<Texture> m_Texture;
		
		//This is where stuff gets weird. This needs some explaining
		rect2f m_LocalBounds;

		rect2f m_TextureRectangle;
		rect2f m_UVRectangle;
	public:
		Sprite(std::shared_ptr<Texture> texture);
		Sprite(std::shared_ptr<Texture> texture, const rect2f &rectangle);
		~Sprite() = default;
	protected:
		void recalculateUVRectangle();
		void recalculateLocalBounds();
	};
}