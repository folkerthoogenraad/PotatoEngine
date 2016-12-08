#include "mat4.h"
#include "mat3.h"

#include "vec3.h"
#include "vec4.h"

namespace ftec {

	template <typename T>
	mat4<T>::mat4()
	{
		std::fill(elements.begin(), elements.end(), (T)0);
		elements[0 + 0 * 4] = (T)1;
		elements[1 + 1 * 4] = (T)1;
		elements[2 + 2 * 4] = (T)1;
		elements[3 + 3 * 4] = (T)1;
	}

	template <typename T>
	mat4<T> mat4<T>::identity()
	{
		return mat4<T>();
	}

	template <typename T>
	mat4<T>& mat4<T>::multiply(const mat4<T>& other)
	{
		//TODO look at this code
		T sum;
		mat4<T> m;

		for (int y = 0; y < 4; ++y) {
			for (int x = 0; x < 4; ++x) {

				sum = 0;
				for (int e = 0; e < 4; ++e) {
					sum += elements[e + y * 4] * other.elements[x + e * 4];
				}
				//is this possible without temp?
				m.elements[x + y * 4] = sum;
			}
		}

		elements = m.elements;

		return *this;
	}

	template <typename T>
	vec4<T> mat4<T>::multiply(const vec4<T> & other) const
	{
		return vec4<T>(
			other.x * elements[0 + 0 * 4] + other.y * elements[1 + 0 * 4] + other.z * elements[2 + 0 * 4] + other.w * elements[3 + 0 * 4],
			other.x * elements[0 + 1 * 4] + other.y * elements[1 + 1 * 4] + other.z * elements[2 + 1 * 4] + other.w * elements[3 + 1 * 4],
			other.x * elements[0 + 2 * 4] + other.y * elements[1 + 2 * 4] + other.z * elements[2 + 2 * 4] + other.w * elements[3 + 2 * 4],
			other.x * elements[0 + 3 * 4] + other.y * elements[1 + 3 * 4] + other.z * elements[2 + 3 * 4] + other.w * elements[3 + 3 * 4]
		);
	}

	template <typename T>
	vec3<T> mat4<T>::multiply(const vec3<T> & other) const
	{
		return vec3<T>(
			other.x * elements[0 + 0 * 4] + other.y * elements[1 + 0 * 4] + other.z * elements[2 + 0 * 4] + elements[3 + 0 * 4],
			other.x * elements[0 + 1 * 4] + other.y * elements[1 + 1 * 4] + other.z * elements[2 + 1 * 4] + elements[3 + 1 * 4],
			other.x * elements[0 + 2 * 4] + other.y * elements[1 + 2 * 4] + other.z * elements[2 + 2 * 4] + elements[3 + 2 * 4]
		);
	}

	template<typename T>
	mat4<T> mat4<T>::operator*(const mat4<T>& right)
	{
		return mat4<T>(*this).multiply(right);
	}

	template <typename T>
	mat4<T> mat4<T>::operator*=(const mat4<T>& right)
	{
		return multiply(right);
	}

	template<typename T>
	vec4<T> mat4<T>::operator*(const vec4<T> & right) const
	{
		return multiply(right);
	}

	template<typename T>
	vec3<T> mat4<T>::operator*(const vec3<T> & right) const
	{
		return multiply(right);
	}

	template <typename T>
	mat4<T> mat4<T>::translation(const vec3<T>& translation)
	{
		mat4<T> result;

		result.elements[3 + 0 * 4] = translation.x;
		result.elements[3 + 1 * 4] = translation.y;
		result.elements[3 + 2 * 4] = translation.z;

		return result;
	}

	template <typename T>
	mat4<T> mat4<T>::rotation(T angle, const vec3<T>& axis)
	{
		mat4<T> result;

		T r = angle * ((T)3.141592654 / (T)180.0);
		T c = cos(r);
		T s = sin(r);
		T omc = 1 - c;

		T x = axis.x;
		T y = axis.y;
		T z = axis.z;

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

	template <typename T>
	mat4<T> mat4<T>::scale(const vec3<T>& scale)
	{
		mat4<T> result;

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

	template <typename T>
	mat4<T> mat4<T>::rotationX(T angle)
	{
		mat4<T> result;

		T r = (T) angle * ((T)3.141592654 / (T)180.0);
		T s = sin(r);
		T c = cos(r);

		result.elements[0 + 0 * 4] = (T)1;

		result.elements[1 + 1 * 4] = c;
		result.elements[2 + 1 * 4] = -s;

		result.elements[1 + 2 * 4] = s;
		result.elements[2 + 2 * 4] = c;

		result.elements[3 + 3 * 4] = (T) 1;

		return result;
	}

	template <typename T>
	mat4<T> mat4<T>::rotationY(T angle)
	{
		mat4<T> result;

		T r = angle * ((T)3.141592654 / (T)180.0);
		T s = sin(r);
		T c = cos(r);

		result.elements[1 + 1 * 4] = 1;

		result.elements[0 + 0 * 4] = c;
		result.elements[2 + 0 * 4] = s;
		result.elements[0 + 2 * 4] = -s;
		result.elements[2 + 2 * 4] = c;

		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	template <typename T>
	mat4<T> mat4<T>::rotationZ(T angle)
	{
		mat4<T> result;

		T r = angle * ((T)3.141592654 / (T)180.0);
		T s = sin(r);
		T c = cos(r);

		result.elements[0 + 0 * 4] = c;
		result.elements[1 + 0 * 4] = -s;
		result.elements[1 + 0 * 4] = s;
		result.elements[1 + 1 * 4] = c;

		result.elements[2 + 2 * 4] = 1;
		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	template <typename T>
	mat4<T> mat4<T>::orthographic(T l, T r, T b, T t, T n, T f)
	{
		mat4<T> result;

		result.elements[0 + 0 * 4] = (T)2.0 / (r - l);
		result.elements[1 + 1 * 4] = (T)2.0 / (t - b);
		result.elements[2 + 2 * 4] = (T)2.0 / (n - f);

		result.elements[3 + 0 * 4] = (l + r) / (l - r);
		result.elements[3 + 1 * 4] = (b + t) / (b - t);
		result.elements[3 + 2 * 4] = (f + n) / (f - n);

		return result;
	}

	template <typename T>
	mat4<T> mat4<T>::perspective(T fov, T asp, T near, T far)
	{
		mat4<T> result;

		T q = (T)1.0 / tan((T)0.5 * fov * ((T)3.141592653 / (T)180.0));
		T a = q / asp;

		T b = (near + far) / (near - far);
		T c = (2 * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;

		result.elements[3 + 2 * 4] = c;
		result.elements[2 + 3 * 4] = -1;
		result.elements[3 + 3 * 4] = 0;

		return result;
	}

	template <typename T>
	mat4<T> mat4<T>::lookAt(const vec3<T> & eye, const vec3<T> & center, const vec3<T> & up)
	{
		mat4<T> result;

		vec3<T> zaxis = (center - eye).normalize();
		vec3<T> xaxis = vec3<T>::cross(up, zaxis).normalize();
		vec3<T> yaxis = vec3<T>::cross(zaxis, xaxis);

		result.elements[0 + 0 * 4] = xaxis.x;
		result.elements[1 + 0 * 4] = xaxis.y;
		result.elements[2 + 0 * 4] = xaxis.z;
		result.elements[3 + 0 * 4] = -vec3<T>::dot(xaxis, eye);

		result.elements[0 + 1 * 4] = yaxis.x;
		result.elements[1 + 1 * 4] = yaxis.y;
		result.elements[2 + 1 * 4] = yaxis.z;
		result.elements[3 + 1 * 4] = -vec3<T>::dot(yaxis, eye);

		result.elements[0 + 2 * 4] = zaxis.x;
		result.elements[1 + 2 * 4] = zaxis.y;
		result.elements[2 + 2 * 4] = zaxis.z;
		result.elements[3 + 2 * 4] = -vec3<T>::dot(zaxis, eye);

		result.elements[0 + 3 * 4] = 0;
		result.elements[1 + 3 * 4] = 0;
		result.elements[2 + 3 * 4] = 0;
		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	template <typename T>
	T mat4<T>::determinant() const
	{
		//[a b c d]
		//[e f g h]
		//[i j k l]
		//[m n o p]
		mat3<T> sub1 = mat3<T>({
			f,g,h,
			j,k,l,
			n,o,p
		});
		mat3<T> sub2 = mat3<T>({
			g,h,e,
			k,l,i,
			o,p,m
		});
		mat3<T> sub3 = mat3<T>({
			h,e,f,
			l,i,j,
			p,m,n
		});
		mat3<T> sub4 = mat3<T>({
			e,f,g,
			i,j,k,
			m,n,o
		});

		return
			a * sub1.determinant()
			- b * sub2.determinant()
			+ c * sub3.determinant()
			- d * sub4.determinant();
	}


	template <typename T>
	mat4<T> mat4<T>::fromForward(const vec3<T> & forward, const vec3<T> & up)
	{
		vec3<T> zaxis = forward;
		vec3<T> xaxis = vec3<T>::cross(up, zaxis);
		vec3<T> yaxis = vec3<T>::cross(zaxis, xaxis);

		mat4<T> result;

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

	//Tell the compiler to pretty pretty please compile this 
	template struct mat4<float>;
	template struct mat4<double>;
}