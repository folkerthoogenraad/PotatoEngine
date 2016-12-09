#include "StairAlgorithm.h"
#include "StairArc.h"
#include "logger/log.h"
#include <assert.h>

namespace ftec {

	float StairAlgorithm::getLength()
	{
		if (m_Vertices.size() < 2)
			return 0;
		if (m_Vertices.size() == 2) {
			return (m_Vertices[0].m_Position - m_Vertices[1].m_Position).magnitude();
		}

		float length = 0;

		for (int i = 1; i < m_Vertices.size(); i++) {
			int previousIndex = i - 1;
			int currentIndex = i;

			auto &previous = m_Vertices[previousIndex];
			auto &current = m_Vertices[currentIndex];

			//Calculate the raw length of this piece
			length += (current.m_Position - previous.m_Position).magnitude();

			//The last also has no curve
			if (!isLast(currentIndex)) {
				length -= current.m_Range;
				StairArc arc = getArc(currentIndex);
				length += arc.getArcLength();
			}

			//The first has no curve
			if (!isFirst(previousIndex)) {
				length -= previous.m_Range;
			}
			
		}

		return length;
	}

	Vector2f StairAlgorithm::getPosition(float distance)
	{
		if (m_Vertices.size() == 0)
			return Vector2f(0, 0);
		else if (m_Vertices.size() == 1 || distance <= 0) 
			return m_Vertices[0].m_Position;
		else if (m_Vertices.size() == 2) {
			Vector2f v = m_Vertices[1].m_Position - m_Vertices[0].m_Position;
			float length =  (v).magnitude();
			v /= length;

			return m_Vertices[0].m_Position + v * distance;
		}

		//we need to calculate the length, sadly enough
		float left = distance;

		for (int i = 1; i < m_Vertices.size(); i++) {
			int previousIndex = i - 1;
			int currentIndex = i;

			auto &previous = m_Vertices[previousIndex];
			auto &current = m_Vertices[currentIndex];

			//Calculate the raw length of this piece
			Vector2f dir = current.m_Position - previous.m_Position;
			float or = dir.magnitude();
			float straightLength = dir.magnitude();
			
			float curveLength = 0;

			//The first has no curve
			if (!isFirst(previousIndex)) {
				straightLength -= previous.m_Range;
			}
			if (!isLast(currentIndex)) {
				straightLength -= current.m_Range;

				StairArc arc = getArc(currentIndex);
				curveLength = arc.getArcLength();
			}

			dir.normalize();

			//We are currently in a straight part!
			if (left < straightLength) {
				float f = left;
				
				if (!isFirst(previousIndex)) {
					f += previous.m_Range;
				}

				return previous.m_Position + dir * f;
			}
			left -= straightLength;

			//We are in the middle of the curve right now
			if (left < curveLength) {
				StairArc arc = getArc(currentIndex);

				float f = left / arc.getArcLength();

				float startAngle = arc.getStartAngle();
				float currentAngle = arc.getAngle() * f * arc.getSide();

				return arc.getOrigin()
					+ Vector2f(
						cosf(startAngle + currentAngle),
						sinf(startAngle + currentAngle)) * arc.getRadius();
			}
			left -= curveLength;
		}

		//Return the last
		return m_Vertices.back().m_Position;
	}

	StairArc StairAlgorithm::getArc(int index)
	{
		//The first and last don't have curve, since this is a private method, it should just crash if the algorithm does use this
		assert(!isFirst(index) && !isLast(index));

		int previousIndex = index - 1;
		int currentIndex = index;
		int nextIndex = index + 1;

		auto &previous = m_Vertices[previousIndex];
		auto &current = m_Vertices[currentIndex];
		auto &next = m_Vertices[nextIndex];
		
		return StairArc(previous.m_Position, current.m_Position, next.m_Position, current.m_Range);
	}

	bool StairAlgorithm::isFirst(int index)
	{
		return index == 0;
	}

	bool StairAlgorithm::isLast(int index)
	{
		return index + 1 == m_Vertices.size();
	}

}
