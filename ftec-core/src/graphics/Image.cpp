#include "Image.h"

namespace ftec {
	
	Image::Image(int width, int height)
		: m_Width(width), m_Height(height)
	{
		m_Data.resize(m_Width * m_Height);
	}

	Color32 Image::getColor(int x, int y) const
	{
		return m_Data[x + y * m_Width];
	}

	void Image::setColor(int x, int y, Color32 c) 
	{
		m_Data[x + y * m_Width] = c;
	}

}
