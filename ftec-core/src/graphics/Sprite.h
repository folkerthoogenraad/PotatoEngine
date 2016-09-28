#pragma once

#include <memory>
#include "math/rect.h"

namespace ftec {
	class Texture;

	class Sprite {
	private:
		std::shared_ptr<Texture> m_Texture;
		
		//This is where stuff gets weird. This needs some explaining
		rect2f m_LocalBounds;

		rect2f m_TextureRectangle;
		rect2f m_UVRectangle;
	public:
		Sprite(std::shared_ptr<Texture> texture);
		Sprite(std::shared_ptr<Texture> texture, const rect2f &rectangle);
		~Sprite() = default;

		//Returns the uv rectangle
		rect2f &uvs() { return m_UVRectangle; };
		const rect2f &uvs() const { return m_UVRectangle; };

		//Returns the bounds
		rect2f &bounds() { return m_LocalBounds; };
		const rect2f &bounds() const { return m_LocalBounds; };

		//Returns the bounds
		std::shared_ptr<Texture> &texture() { return m_Texture; };
		const std::shared_ptr<Texture> &texture() const { return m_Texture; };
	protected:
		void recalculateUVRectangle();
		void recalculateLocalBounds();
	};
}