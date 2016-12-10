#pragma once

#include <memory>
#include "math/rect.h"

namespace ftec {
	class Texture;

	class Sprite {
	private:
		std::shared_ptr<Texture> m_Texture = 0;
		
		//This is where stuff gets weird. This needs some explaining
		rectf m_LocalBounds;

		rectf m_TextureRectangle;
		rectf m_UVRectangle;
	public:
		Sprite() = default;
		Sprite(std::shared_ptr<Texture> texture);
		Sprite(std::shared_ptr<Texture> texture, const rectf &rectangle);
		~Sprite() = default;

		//Returns the uv rectangle
		rectf &uvs() { return m_UVRectangle; };
		const rectf &uvs() const { return m_UVRectangle; };

		//Returns the bounds
		rectf &bounds() { return m_LocalBounds; };
		const rectf &bounds() const { return m_LocalBounds; };

		//Returns the bounds
		std::shared_ptr<Texture> &texture() { return m_Texture; };
		const std::shared_ptr<Texture> &texture() const { return m_Texture; };
	protected:
		void recalculateUVRectangle();
		void recalculateLocalBounds();
	};
}