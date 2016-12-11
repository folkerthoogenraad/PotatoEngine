#pragma once

#include <memory>
#include "math/Rectangle.h"

namespace ftec {
	class Texture;

	class Sprite {
	private:
		std::shared_ptr<Texture> m_Texture = 0;
		
		//This is where stuff gets weird. This needs some explaining
		Rectanglef m_LocalBounds;

		Rectanglef m_TextureRectangle;
		Rectanglef m_UVRectangle;
	public:
		Sprite() = default;
		Sprite(std::shared_ptr<Texture> texture);
		Sprite(std::shared_ptr<Texture> texture, const Rectanglef &rectangle);
		~Sprite() = default;

		//Returns the uv rectangle
		Rectanglef &uvs() { return m_UVRectangle; };
		const Rectanglef &uvs() const { return m_UVRectangle; };

		//Returns the bounds
		Rectanglef &bounds() { return m_LocalBounds; };
		const Rectanglef &bounds() const { return m_LocalBounds; };

		//Returns the bounds
		std::shared_ptr<Texture> &texture() { return m_Texture; };
		const std::shared_ptr<Texture> &texture() const { return m_Texture; };
	protected:
		void recalculateUVRectangle();
		void recalculateLocalBounds();
	};
}