#pragma once

#include <vector>
#include "math/Vector4.h"

namespace ftec {

	class Image {
	private:
		std::vector<Color32> m_Data;
		int m_Width;
		int m_Height;
	public:
		Image(int width, int height);

		Color32 getColor(int x, int y) const;
		void setColor(int x, int y, Color32 c);

		const std::vector<Color32> &getColors() const { return m_Data; };
		std::vector<Color32> &getColors() { return m_Data; };

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
	};

}