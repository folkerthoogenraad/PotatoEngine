#include "StairArc.h"

#include "math/math.h"

namespace ftec {
	
	StairArc::StairArc(Vector2f a, Vector2f b, Vector2f c, float distance)
		:m_Point{ a,b,c }, m_Distance(distance)
	{

	}

	float StairArc::getStartAngle() const
	{
		Vector2f from = (getOrigin() - getArcStart()).normalize();

		return atan2(-from.y, -from.x); //Note: atan2 has x and y reversed :)
	}

	float StairArc::getAngle() const
	{
		Vector2f from = (getArcStart() - getOrigin()).normalize();
		Vector2f to = (getArcEnd() - getOrigin()).normalize();

		float d = Vector2f::dot(to, from);
		return acos(d);
	}

	float StairArc::getRadius() const
	{
		Vector2f p = getArcStart();
		Vector2f q = getArcEnd();

		Vector2f r = Vector2f::perp((getCenter() - getStart()).normalize());
		Vector2f s = Vector2f::perp((getEnd() - getCenter()).normalize());

		float t = Vector2f::cross(q - p, s) / Vector2f::cross(r, s);

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

	Vector2f StairArc::getArcStart() const
	{
		Vector2f direction = (getStart() - getCenter()).normalize();
		return getCenter() + direction * m_Distance;
	}

	Vector2f StairArc::getArcEnd() const
	{
		Vector2f direction = (getEnd() - getCenter()).normalize();
		return getCenter() + direction * m_Distance;
	}

	Vector2f StairArc::getOrigin() const
	{
		Vector2f p = getArcStart();
		Vector2f q = getArcEnd();

		Vector2f r = Vector2f::perp((getCenter() - getStart()).normalize());
		Vector2f s = Vector2f::perp((getEnd() - getCenter()).normalize());

		float t = Vector2f::cross(q - p, s) / Vector2f::cross(r, s);

		return p + r * t;
	}

	float StairArc::getSide() const
	{
		Vector2f from = (getStart() - getCenter()).normalize();
		Vector2f to = (getEnd() - getCenter()).normalize();

		Vector2f r = Vector2f::perp(from);

		return sign(Vector2f::dot(to, r));
	}

}