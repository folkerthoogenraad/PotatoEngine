#pragma once

#include <memory>
#include "math/Rectangle.h"

namespace ftec {
	class Texture;

	class Sprite {
	private:
		std::shared_ptr<Texture> m_Texture = 0;
		
		//This needs to be fixed though. 
		//This is where stuff gets weird. This needs some explaining

		Vector2f m_Size;
		Vector2f m_Offset;

		Rectanglef m_UVRectangle;
	public:
		Sprite() = default;
		Sprite(std::shared_ptr<Texture> texture);
		Sprite(std::shared_ptr<Texture> texture, const Rectanglef &rectangle);
		~Sprite() = default;

		//Returns the uv rectangle
		Rectanglef &uvs() { return m_UVRectangle; };
		const Rectanglef &uvs() const { return m_UVRectangle; };

		//Returns the size
		Vector2f &size() { return m_Size; };
		const Vector2f &size() const { return m_Size; };
		
		//Returns the offset, in 0 - 1 starting from the bottom left
		Vector2f &offset() { return m_Offset; };
		const Vector2f &offset() const { return m_Offset; };

		Rectanglef bounds() const { return Rectanglef(
			-size().x * offset().x,
			-size().y * offset().y,
			size().x,
			size().y
		); }

		//Returns the bounds
		std::shared_ptr<Texture> &texture() { return m_Texture; };
		const std::shared_ptr<Texture> &texture() const { return m_Texture; };
	protected:
		void recalculateUVRectangle(const Rectanglef &textureRectangle);
		void recalculateLocalBounds(const Rectanglef &textureRectangle);
	};
}