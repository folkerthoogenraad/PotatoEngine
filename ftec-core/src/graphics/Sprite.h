#pragma once

#include <memory>
#include "math/Rectangle.h"

namespace ftec {
	class Texture;

	struct SpriteSlices {
		SpriteSlices();
		SpriteSlices(float top, float bottom, float left, float right);
		float top = 0, bottom = 0;
		float left = 0, right = 0;
	};

	class Sprite {
	public:
		enum SpriteType {
			Default,
			Sliced, // 9 sided
			Tiled,
			SlicedAndTiled
		};
	private:
		std::shared_ptr<Texture> m_Texture = 0;
		
		//This needs to be fixed though. 
		//This is where stuff gets weird. This needs some explaining

		Vector2f m_Size;
		Vector2f m_Offset;

		Rectanglef m_UVRectangle;

		SpriteType m_SpriteType = Default;
		SpriteSlices m_Slices;

	public:
		Sprite() = default;
		Sprite(std::shared_ptr<Texture> texture);
		Sprite(std::shared_ptr<Texture> texture, const Rectanglef &rectangle);
		~Sprite() = default;

		//Returns the uv rectangle
		Rectanglef &uvs() { return m_UVRectangle; };
		const Rectanglef &uvs() const { return m_UVRectangle; };

		//Returns the size (not modifyable)
		const Vector2f &size() const { return m_Size; };
		
		// Returns the offset in pixels
		Vector2f &offset() { return m_Offset; };
		const Vector2f &offset() const { return m_Offset; };

		//Returns the bounds
		Rectanglef bounds() const { return Rectanglef(
			-offset().x,
			-offset().y,
			-offset().x + size().x,
			-offset().y + size().y
		); }

		Sprite &flipY();

		// Type stuff
		inline Sprite &setType(SpriteType type) { m_SpriteType = type; return *this; }
		inline SpriteType getType() const { return m_SpriteType; }

		// Returns the texture, nicely
		std::shared_ptr<Texture> &texture() { return m_Texture; };
		const std::shared_ptr<Texture> &texture() const { return m_Texture; };

		// Sliced stuff
		inline Sprite &setSlices(SpriteSlices slices) { m_Slices = std::move(slices); return *this; };
		inline SpriteSlices getSlices() const { return m_Slices;  }
	protected:
		void recalculateUVRectangle(const Rectanglef &textureRectangle);
		void recalculateLocalBounds(const Rectanglef &textureRectangle);
	};
}