#pragma once

#include "math/math.h"
#include <array>

namespace ftec {

	struct StairArc {
	private:
		const std::array<const vec2f, 3> m_Point;
		float m_Distance;

	public:
		StairArc(vec2f a, vec2f b, vec2f c, float distance);

		float getStartAngle() const;
		float getAngle() const;
		float getRadius() const;

		float getDistance() const;

		void setDistance(float s);		//Sets the distance and calculates the radius based on that
		//TODO setRadius calculation

		float getArcLength() const;

		vec2f getArcStart() const;
		vec2f getArcEnd() const;
		vec2f getOrigin() const;

		//Returns the side this curve goes to ( endAngle = startAngle() + getAngle() * getSide() )
		float getSide() const;

		inline vec2f getStart() const { return m_Point[0]; }
		inline vec2f getCenter() const { return m_Point[1]; }
		inline vec2f getEnd() const { return m_Point[2]; }
		inline vec2f getPoint(int index) { return m_Point[index]; }
	};

}