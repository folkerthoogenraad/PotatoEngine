#include "mat4.h"

namespace ftec{

	mat4::mat4()
	{
		memset(elements, 0, sizeof(elements));
		elements[0 + 0 * 4] = 1;
		elements[1 + 1 * 4] = 1;
		elements[2 + 2 * 4] = 1;
		elements[3 + 3 * 4] = 1;
	}

	mat4 mat4::identity()
	{
		return mat4();
	}

	mat4& mat4::multiply(const mat4& other)
	{
		//TODO look at this code
		float sum;
		mat4 m;

		for (int y = 0; y < 4; ++y){
			for (int x = 0; x < 4; ++x){

				sum = 0;
				for (int e = 0; e < 4; ++e){
					sum += elements[e + y * 4] * other.elements[x + e * 4];
				}
				//is this possible without temp?
				m.elements[x + y * 4] = sum;
			}
		}

		memcpy(elements, m.elements, sizeof(elements));

		return *this;
	}

	vec4 mat4::multiply(const vec4 & other) const
	{
		return vec4(
			other.x * elements[0 + 0 * 4] + other.y * elements[1 + 0 * 4] + other.z * elements[2 + 0 * 4] + other.w * elements[3 + 0 * 4],
			other.x * elements[0 + 1 * 4] + other.y * elements[1 + 1 * 4] + other.z * elements[2 + 1 * 4] + other.w * elements[3 + 1 * 4],
			other.x * elements[0 + 2 * 4] + other.y * elements[1 + 2 * 4] + other.z * elements[2 + 2 * 4] + other.w * elements[3 + 2 * 4],
			other.x * elements[0 + 3 * 4] + other.y * elements[1 + 3 * 4] + other.z * elements[2 + 3 * 4] + other.w * elements[3 + 3 * 4]
		);
	}

	vec3 mat4::multiply(const vec3 & other) const
	{
		return vec3(
			other.x * elements[0 + 0 * 4] + other.y * elements[1 + 0 * 4] + other.z * elements[2 + 0 * 4] + elements[3 + 0 * 4],
			other.x * elements[0 + 1 * 4] + other.y * elements[1 + 1 * 4] + other.z * elements[2 + 1 * 4] + elements[3 + 1 * 4],
			other.x * elements[0 + 2 * 4] + other.y * elements[1 + 2 * 4] + other.z * elements[2 + 2 * 4] + elements[3 + 2 * 4]
		);
	}

	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.multiply(right);
	}

	vec4 operator*(const mat4 &left, const vec4 & right)
	{
		return left.multiply(right);
	}

	vec3 operator*(const mat4 &left, const vec3 & right)
	{
		return left.multiply(right);
	}

	mat4 mat4::operator*=(const mat4& right)
	{
		return multiply(right);
	}


	std::ostream& operator<<(std::ostream& left, const mat4& right)
	{
		for (int row = 0; row < 4; ++row){
			left << "[";
			for (int column = 0; column < 4; ++column){
				left << right.elements[column + row * 4];
				if (column != 3)
					left << ", ";
			}
			left << "]" << std::endl;
		}

		return left;
	}

	mat4 mat4::translation(const vec3& translation)
	{
		mat4 result;

		result.elements[3 + 0 * 4] = translation.x;
		result.elements[3 + 1 * 4] = translation.y;
		result.elements[3 + 2 * 4] = translation.z;

		return result;
	}

	mat4 mat4::rotation(float angle, const vec3& axis)
	{
		mat4 result;

		float r = angle * (3.141592654 / 180);
		float c = cos(r);
		float s = sin(r);
		float omc = 1 - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[0 + 1 * 4] = y * x * omc + z * s;
		result.elements[0 + 2 * 4] = x * z * omc - y * s;

		result.elements[1 + 0 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[1 + 2 * 4] = y * z * omc + x * s;

		result.elements[2 + 0 * 4] = x * z * omc + y * s;
		result.elements[2 + 1 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;

		return result;
	}

	mat4 mat4::scale(const vec3& scale)
	{
		mat4 result;

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

	mat4 mat4::orthographic(float l, float r, float b, float t, float n, float f)
	{
		mat4 result;

		//row + column * 4

		result.elements[0 + 0 * 4] = 2.0f / (r - l);
		result.elements[1 + 1 * 4] = 2.0f / (t - b);
		result.elements[2 + 2 * 4] = 2.0f / (n - f);

		result.elements[0 + 3 * 4] = (l + r) / (l - r);
		result.elements[1 + 3 * 4] = (b + t) / (b - t);
		result.elements[2 + 3 * 4] = (f + n) / (f - n);

		return result;
	}

	mat4 mat4::perspective(float fov, float asp, float near, float far)
	{
		mat4 result;

		float q = 1.0f / tan(0.5f * fov * (3.141592653 / 180));
		float a = q / asp;

		float b = -(near + far) / (near - far);
		float c = (2 * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;

		result.elements[3 + 2 * 4] = c;
		result.elements[2 + 3 * 4] = -1;

		return result;
	}

}
