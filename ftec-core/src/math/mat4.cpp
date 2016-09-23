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

	vec4f mat4::multiply(const vec4f & other) const
	{
		return vec4f(
			other.x * elements[0 + 0 * 4] + other.y * elements[1 + 0 * 4] + other.z * elements[2 + 0 * 4] + other.w * elements[3 + 0 * 4],
			other.x * elements[0 + 1 * 4] + other.y * elements[1 + 1 * 4] + other.z * elements[2 + 1 * 4] + other.w * elements[3 + 1 * 4],
			other.x * elements[0 + 2 * 4] + other.y * elements[1 + 2 * 4] + other.z * elements[2 + 2 * 4] + other.w * elements[3 + 2 * 4],
			other.x * elements[0 + 3 * 4] + other.y * elements[1 + 3 * 4] + other.z * elements[2 + 3 * 4] + other.w * elements[3 + 3 * 4]
		);
	}

	vec3f mat4::multiply(const vec3f & other) const
	{
		return vec3f(
			other.x * elements[0 + 0 * 4] + other.y * elements[1 + 0 * 4] + other.z * elements[2 + 0 * 4] + elements[3 + 0 * 4],
			other.x * elements[0 + 1 * 4] + other.y * elements[1 + 1 * 4] + other.z * elements[2 + 1 * 4] + elements[3 + 1 * 4],
			other.x * elements[0 + 2 * 4] + other.y * elements[1 + 2 * 4] + other.z * elements[2 + 2 * 4] + elements[3 + 2 * 4]
		);
	}

	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.multiply(right);
	}

	vec4f operator*(const mat4 &left, const vec4f & right)
	{
		return left.multiply(right);
	}

	vec3f operator*(const mat4 &left, const vec3f & right)
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

	mat4 mat4::translation(const vec3f& translation)
	{
		mat4 result;

		result.elements[3 + 0 * 4] = translation.x;
		result.elements[3 + 1 * 4] = translation.y;
		result.elements[3 + 2 * 4] = translation.z;

		return result;
	}

	mat4 mat4::rotation(float angle, const vec3f& axis)
	{
		mat4 result;

		float r = angle * (3.141592654f / 180.f);
		float c = cos(r);
		float s = sin(r);
		float omc = 1 - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[1 + 0 * 4] = y * x * omc + z * s;
		result.elements[2 + 0 * 4] = x * z * omc - y * s;

		result.elements[0 + 1 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[2 + 1 * 4] = y * z * omc + x * s;

		result.elements[0 + 2 * 4] = x * z * omc + y * s;
		result.elements[1 + 2 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;

		return result;
	}

	mat4 mat4::scale(const vec3f& scale)
	{
		mat4 result;

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

	mat4 mat4::rotationX(float angle)
	{
		mat4 result;

		float r = angle * (3.141592654f / 180.f);
		float s = sin(r);
		float c = cos(r);

		result.elements[0 + 0 * 4] = 1;
		
		result.elements[1 + 1 * 4] = c;
		result.elements[2 + 1 * 4] = -s;

		result.elements[1 + 2 * 4] = s;
		result.elements[2 + 2 * 4] = c;

		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	mat4 mat4::rotationY(float angle)
	{
		mat4 result;

		float r = angle * (3.141592654f / 180.f);
		float s = sin(r);
		float c = cos(r);

		result.elements[1 + 1 * 4] = 1;

		result.elements[0 + 0 * 4] = c;
		result.elements[2 + 0 * 4] = s;
		result.elements[0 + 2 * 4] = -s;
		result.elements[2 + 2 * 4] = c;

		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	mat4 mat4::rotationZ(float angle)
	{
		mat4 result;

		float r = angle * (3.141592654f / 180.f);
		float s = sin(r);
		float c = cos(r);

		result.elements[0 + 0 * 4] = c;
		result.elements[1 + 0 * 4] = -s;
		result.elements[1 + 0 * 4] = s;
		result.elements[1 + 1 * 4] = c;

		result.elements[2 + 2 * 4] = 1;
		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	mat4 mat4::orthographic(float l, float r, float b, float t, float n, float f)
	{
		mat4 result;

		result.elements[0 + 0 * 4] = 2.0f / (r - l);
		result.elements[1 + 1 * 4] = 2.0f / (t - b);
		result.elements[2 + 2 * 4] = 2.0f / (n - f);

		result.elements[3 + 0 * 4] = (l + r) / (l - r);
		result.elements[3 + 1 * 4] = (b + t) / (b - t);
		result.elements[3 + 2 * 4] = (f + n) / (f - n);

		return result;
	}

	mat4 mat4::perspective(float fov, float asp, float near, float far)
	{
		mat4 result;

		float q = 1.0f / tan(0.5f * fov * (3.141592653f / 180.f));
		float a = q / asp;

		float b = (near + far) / (near - far);
		float c = (2 * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;

		result.elements[3 + 2 * 4] = c;
		result.elements[2 + 3 * 4] = -1;
		result.elements[3 + 3 * 4] = 0;

		return result;
	}

	mat4 mat4::lookAt(const vec3f & eye, const vec3f & center, const vec3f & up)
	{
		mat4 result;

		vec3f zaxis = (center - eye).normalize();
		vec3f xaxis = vec3f::cross(up, zaxis).normalize();
		vec3f yaxis = vec3f::cross(zaxis, xaxis);

		result.elements[0 + 0 * 4] = xaxis.x;
		result.elements[1 + 0 * 4] = xaxis.y;
		result.elements[2 + 0 * 4] = xaxis.z;
		result.elements[3 + 0 * 4] = -vec3f::dot(xaxis, eye);

		result.elements[0 + 1 * 4] = yaxis.x;
		result.elements[1 + 1 * 4] = yaxis.y;
		result.elements[2 + 1 * 4] = yaxis.z;
		result.elements[3 + 1 * 4] = -vec3f::dot(yaxis, eye);

		result.elements[0 + 2 * 4] = zaxis.x;
		result.elements[1 + 2 * 4] = zaxis.y;
		result.elements[2 + 2 * 4] = zaxis.z;
		result.elements[3 + 2 * 4] = -vec3f::dot(zaxis, eye);

		result.elements[0 + 3 * 4] = 0;
		result.elements[1 + 3 * 4] = 0;
		result.elements[2 + 3 * 4] = 0;
		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	//TODO look at the resulting matrix, see if it looks a bit correctish
	mat4 mat4::fromForward(const vec3f & forward, const vec3f & up)
	{
		vec3f zaxis = forward;
		vec3f xaxis = vec3f::cross(up, zaxis);
		vec3f yaxis = vec3f::cross(zaxis, xaxis);

		mat4 result;

		result.elements[0 + 0 * 4] = xaxis.x;
		result.elements[1 + 0 * 4] = xaxis.y;
		result.elements[2 + 0 * 4] = xaxis.z;

		result.elements[0 + 1 * 4] = yaxis.x;
		result.elements[1 + 1 * 4] = yaxis.y;
		result.elements[2 + 1 * 4] = yaxis.z;

		result.elements[0 + 2 * 4] = zaxis.x;
		result.elements[1 + 2 * 4] = zaxis.y;
		result.elements[2 + 2 * 4] = zaxis.z;

		return result;
	}

}
