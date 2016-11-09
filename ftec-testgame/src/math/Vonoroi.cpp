#include "Vonoroi.h"

namespace ftec {

	const vec2f & ftec::Vonoroi::getPoint(int index) const
	{
		return m_Points[index];
	}

	int Vonoroi::getPointCount() const
	{
		return m_Points.size();
	}

}
