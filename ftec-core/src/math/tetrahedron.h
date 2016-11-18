#pragma once

#include "vec3.h"
#include "sphere.h"
#include "mat4.h"
#include "triangle3.h"

namespace ftec {

	template<typename T>
	struct tetrahedron {
		vec3<T> a;
		vec3<T> b;
		vec3<T> c;
		vec3<T> d;

		tetrahedron() {}
		tetrahedron(const vec3<T> &a, const vec3<T> &b, const vec3<T> &c, const vec3<T> &d)
			: a(a), b(b), c(c), d(d) {}

		sphere<T> circumsphere()
		{
			//http://mathworld.wolfram.com/Circumsphere.html
			//Don't even bother

			float aa = mat4({
				a.x, a.y, a.z, 1,
				b.x, b.y, b.z, 1,
				c.x, c.y, c.z, 1,
				d.x, d.y, d.z, 1
			}).determinant();

			float dx = mat4({
				a.sqrmagnitude(), a.y, a.z, 1,
				b.sqrmagnitude(), b.y, b.z, 1,
				c.sqrmagnitude(), c.y, c.z, 1,
				d.sqrmagnitude(), d.y, d.z, 1
			}).determinant();

			float dy = -mat4({
				a.sqrmagnitude(), a.x, a.z, 1,
				b.sqrmagnitude(), b.x, b.z, 1,
				c.sqrmagnitude(), c.x, c.z, 1,
				d.sqrmagnitude(), d.x, d.z, 1
			}).determinant();

			float dz = mat4({
				a.sqrmagnitude(), a.x, a.y, 1,
				b.sqrmagnitude(), b.x, b.y, 1,
				c.sqrmagnitude(), c.x, c.y, 1,
				d.sqrmagnitude(), d.x, d.y, 1
			}).determinant();

			float cc = mat4({
				a.sqrmagnitude(), a.x, a.y, a.z,
				b.sqrmagnitude(), b.x, b.y, b.z,
				c.sqrmagnitude(), c.x, c.y, c.z,
				d.sqrmagnitude(), d.x, d.y, d.z
			}).determinant();

			return sphere<T>(
				vec3f(dx / (2 * aa), dy / (2 * aa), dz / (2 * aa)),
				sqrt(dx * dx + dy * dy + dz * dz - 4 * aa * cc) / (2.0f * abs(aa))
				);
		}

		tetrahedron<T> multiplied(mat4 m) const
		{
			return tetrahedron<T>(
				m * a,
				m * b,
				m * c,
				m * d );
		}

		//TODO check the winding of these triangles, they should at least be the same
		triangle3<T> triangleabc() const { return triangle3<T>(a, b, c); }
		triangle3<T> triangleabd() const { return triangle3<T>(a, b, d); }
		triangle3<T> triangledbc() const { return triangle3<T>(d, b, c); }
		triangle3<T> triangleacd() const { return triangle3<T>(a, c, d); }
	
		static tetrahedron<T> unitTetrahedron()
		{
			//See trigonometry for this one :)
			float w = sqrt(0.75) / 3.f;
			float h = sqrt( 1 - (2 * w) * (2 * w) ) / 3.f;

			return tetrahedron<T>(
				vec3<T>(-0.5f, -h, -w),
				vec3<T>(0.5f, -h, -w),
				vec3<T>(0, -h, 2.f * w),
				vec3<T>(0, 2 * h, 0)
				);
		}
	};

	typedef tetrahedron<float> tetrahedronf;
	typedef tetrahedron<double> tetrahedrond;
	typedef tetrahedron<int> tetrahedroni;

}