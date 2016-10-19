#include "StairArc.h"

namespace ftec {
	
	StairArc::StairArc(vec2f a, vec2f b, vec2f c, float distance)
		:m_Point{ a,b,c }, m_Distance(distance)
	{

	}

	float StairArc::getStartAngle() const
	{
		vec2f from = (getOrigin() - getArcStart()).normalize();

		return atan2(-from.y, -from.x); //Note: atan2 has x and y reversed :)
	}

	float StairArc::getAngle() const
	{
		vec2f from = (getArcStart() - getOrigin()).normalize();
		vec2f to = (getArcEnd() - getOrigin()).normalize();

		float d = vec2f::dot(to, from);
		return acos(d);
	}

	float StairArc::getRadius() const
	{
		vec2f p = getArcStart();
		vec2f q = getArcEnd();

		vec2f r = vec2f::perp((getCenter() - getStart()).normalize());
		vec2f s = vec2f::perp((getEnd() - getCenter()).normalize());

		float t = vec2f::cross(q - p, s) / vec2f::cross(r, s);

		return abs(t);
	}

	float StairArc::getDistance() const
	{
		return m_Distance;
	}

	void StairArc::setDistance(float s)
	{
		m_Distance = s;
	}

	float StairArc::getArcLength() const
	{
		return getAngle() * getRadius();
	}

	vec2f StairArc::getArcStart() const
	{
		vec2f direction = (getStart() - getCenter()).normalize();
		return getCenter() + direction * m_Distance;
	}

	vec2f StairArc::getArcEnd() const
	{
		vec2f direction = (getEnd() - getCenter()).normalize();
		return getCenter() + direction * m_Distance;
	}

	vec2f StairArc::getOrigin() const
	{
		vec2f p = getArcStart();
		vec2f q = getArcEnd();

		vec2f r = vec2f::perp((getCenter() - getStart()).normalize());
		vec2f s = vec2f::perp((getEnd() - getCenter()).normalize());

		float t = vec2f::cross(q - p, s) / vec2f::cross(r, s);

		return p + r * t;
	}

	float StairArc::getSide() const
	{
		vec2f from = (getStart() - getCenter()).normalize();
		vec2f to = (getEnd() - getCenter()).normalize();

		vec2f r = vec2f::perp(from);

		return sign(vec2f::dot(to, r));
	}

}