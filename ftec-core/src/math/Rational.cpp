#include "Rational.h"

#include "Vector3.h"

namespace ftec {
	Vector3f toFloat(const Vector3r & v)
	{
		Vector3f out;

		out.x = v.x.convert_to<float>();
		out.y = v.y.convert_to<float>();
		out.z = v.z.convert_to<float>();

		return out;
	}
	Vector3r toRational(const Vector3f & v, int resolution)
	{
		Vector3r result;

		result.x = rational(round(v.x * resolution) / resolution);
		result.y = rational(round(v.y * resolution) / resolution);
		result.z = rational(round(v.z * resolution) / resolution);

		return result;
	}
}