#pragma once

#include "Vector3.h"

namespace ftec {

	template<typename T>
	struct sphere;
	template<typename T>
	struct Matrix4;

	template<typename T>
	struct box {
		Vector3<T> min;
		Vector3<T> max;

		box() {}
		box(Vector3<T> mn, Vector3<T> mx) : min(mn), max(mx) {}

		Vector3<T> center() const { return (min + max) / 2; }
		Vector3<T> extends() const { return max - center(); }

		T magnitude() const { return extends().magnitude(); }

		box<T> &transform(const Matrix4<T> &m)
		{
			min = m * min;
			max = m * max;
			return *this;
		}
		box<T> transformed(const Matrix4<T> &m) const
		{
			return clone().transform(m);
		}

		box<T> &flip()
		{
			Vector3<T> t = max;
			max = min;
			min = t;

			return *this;
		}
		box<T> flipped() const
		{
			return clone().flip();
		}

		box<T> clone() const { return box<T>(*this); }
		sphere<T> boudingsphere() const {
			return sphere<T>(
				(min + max) / 2,
				(max - min).magnitude() / 2
				);
		}
	};

	typedef box<float> boxf;
	typedef box<double> boxd;
	typedef box<int> boxi;
}