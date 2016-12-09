#pragma once

#include "math/Vector2.h"
#include <array>

namespace ftec {

	struct StairArc {
	private:
		const std::array<const Vector2f, 3> m_Point;
		float m_Distance;

	public:
		StairArc(Vector2f a, Vector2f b, Vector2f c, float distance);

		float getStartAngle() const;
		float getAngle() const;
		float getRadius() const;

		float getDistance() const;

		void setDistance(float s);		//Sets the distance and calculates the radius based on that
		//TODO setRadius calculation

		float getArcLength() const;

		Vector2f getArcStart() const;
		Vector2f getArcEnd() const;
		Vector2f getOrigin() const;

		//Returns the side this curve goes to ( endAngle = startAngle() + getAngle() * getSide() )
		float getSide() const;

		inline Vector2f getStart() const { return m_Point[0]; }
		inline Vector2f getCenter() const { return m_Point[1]; }
		inline Vector2f getEnd() const { return m_Point[2]; }
		inline Vector2f getPoint(int index) { return m_Point[index]; }
	};

}