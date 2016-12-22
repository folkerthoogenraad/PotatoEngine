#include "Matrix4.h"
#include "Matrix3.h"

#include "Vector3.h"
#include "Vector4.h"

#include "logger/log.h" //TODO remove ofc

namespace ftec {

	template <typename T>
	Matrix4<T>::Matrix4()
	{
		std::fill(elements.begin(), elements.end(), (T)0);
		elements[0 + 0 * 4] = (T)1;
		elements[1 + 1 * 4] = (T)1;
		elements[2 + 2 * 4] = (T)1;
		elements[3 + 3 * 4] = (T)1;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::identity()
	{
		return Matrix4<T>();
	}

	template<typename T>
	Matrix4<T> Matrix4<T>::inversed() const
	{
		//TODO implement
		return clone().inverse();
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::inverse()
	{

		return *this;
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::multiply(const T & t)
	{
		for (int i = 0; i < elements.size(); i++){
			elements[i] *= t;
		}
		return *this;
	}

	template<typename T>
	Matrix4<T> Matrix4<T>::multiplied(const T & t) const
	{
		return clone().multiply(t);
	}

	template<typename T>
	Matrix4<T> Matrix4<T>::multiplied(const Matrix4 & other) const
	{
		return clone().multiply(other);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::multiply(const Matrix4<T>& other)
	{
		T sum;
		Matrix4<T> m;

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
	Vector4<T> Matrix4<T>::transform(const Vector4<T> & other) const
	{
		return Vector4<T>(
			other.x * elements[0 + 0 * 4] + other.y * elements[1 + 0 * 4] + other.z * elements[2 + 0 * 4] + other.w * elements[3 + 0 * 4],
			other.x * elements[0 + 1 * 4] + other.y * elements[1 + 1 * 4] + other.z * elements[2 + 1 * 4] + other.w * elements[3 + 1 * 4],
			other.x * elements[0 + 2 * 4] + other.y * elements[1 + 2 * 4] + other.z * elements[2 + 2 * 4] + other.w * elements[3 + 2 * 4],
			other.x * elements[0 + 3 * 4] + other.y * elements[1 + 3 * 4] + other.z * elements[2 + 3 * 4] + other.w * elements[3 + 3 * 4]
		);
	}

	template <typename T>
	Vector3<T> Matrix4<T>::transform(const Vector3<T> & other) const
	{
		return Vector3<T>(
			other.x * elements[0 + 0 * 4] + other.y * elements[1 + 0 * 4] + other.z * elements[2 + 0 * 4] + elements[3 + 0 * 4],
			other.x * elements[0 + 1 * 4] + other.y * elements[1 + 1 * 4] + other.z * elements[2 + 1 * 4] + elements[3 + 1 * 4],
			other.x * elements[0 + 2 * 4] + other.y * elements[1 + 2 * 4] + other.z * elements[2 + 2 * 4] + elements[3 + 2 * 4]
		);
	}

	template<typename T>
	Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& right)
	{
		return Matrix4<T>(*this).multiply(right);
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::operator*=(const Matrix4<T>& right)
	{
		return multiply(right);
	}

	template<typename T>
	Vector4<T> Matrix4<T>::operator*(const Vector4<T> & right) const
	{
		return transform(right);
	}

	template<typename T>
	Vector3<T> Matrix4<T>::operator*(const Vector3<T> & right) const
	{
		return transform(right);
	}

	template<typename T>
	Matrix4<T> Matrix4<T>::translation(T x, T y, T z)
	{
		Matrix4<T> result;

		result.elements[3 + 0 * 4] = x;
		result.elements[3 + 1 * 4] = y;
		result.elements[3 + 2 * 4] = z;

		return result;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::translation(const Vector3<T>& t)
	{
		return translation(t.x, t.y, t.z);
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::rotation(T angle, const Vector3<T>& axis)
	{
		Matrix4<T> result;

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

	template<typename T>
	Matrix4<T> Matrix4<T>::scaled(T x, T y, T z)
	{
		Matrix4<T> result;

		result.elements[0 + 0 * 4] = x;
		result.elements[1 + 1 * 4] = y;
		result.elements[2 + 2 * 4] = z;

		return result;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::scaled(const Vector3<T>& s)
	{
		return scaled(s.x, s.y, s.z);
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::rotationX(T angle)
	{
		Matrix4<T> result;

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
	Matrix4<T> Matrix4<T>::rotationY(T angle)
	{
		Matrix4<T> result;

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
	Matrix4<T> Matrix4<T>::rotationZ(T angle)
	{
		Matrix4<T> result;

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

	template<typename T>
	Matrix4<T> Matrix4<T>::clone() const
	{
		return Matrix4<T>(*this);
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::orthographic(T l, T r, T b, T t, T n, T f)
	{
		Matrix4<T> result;

		result.elements[0 + 0 * 4] = (T)2.0 / (r - l);
		result.elements[1 + 1 * 4] = (T)2.0 / (t - b);
		result.elements[2 + 2 * 4] = (T)2.0 / (f - n);

		result.elements[3 + 0 * 4] = -(r + l) / (r - l);
		result.elements[3 + 1 * 4] = -(t + b) / (t - b);
		result.elements[3 + 2 * 4] = -(f + n) / (f - n);

		return result;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::perspective(T fov, T asp, T near, T far)
	{
		Matrix4<T> result;

		T rad = ((T)3.141592653 / (T)180.0);

		T q = (T)1.0 / (tan((T)0.5 * fov * rad) );
		T a = (T)1.0 / (tan((T)0.5 * fov * rad) * asp);

		T b = (far + near) / (far - near);
		T c = -(2 * far * near) / (far - near);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;

		result.elements[3 + 2 * 4] = c;
		result.elements[2 + 3 * 4] = 1;
		result.elements[3 + 3 * 4] = 0;

		return result;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::lookAt(const Vector3<T> & eye, const Vector3<T> & center, const Vector3<T> & up)
	{
		Matrix4<T> result;

		Vector3<T> zaxis = (center - eye).normalize();
		Vector3<T> xaxis = Vector3<T>::cross(up, zaxis).normalize();
		Vector3<T> yaxis = Vector3<T>::cross(zaxis, xaxis);

		result.elements[0 + 0 * 4] = xaxis.x;
		result.elements[1 + 0 * 4] = xaxis.y;
		result.elements[2 + 0 * 4] = xaxis.z;
		result.elements[3 + 0 * 4] = -Vector3<T>::dot(xaxis, eye);

		result.elements[0 + 1 * 4] = yaxis.x;
		result.elements[1 + 1 * 4] = yaxis.y;
		result.elements[2 + 1 * 4] = yaxis.z;
		result.elements[3 + 1 * 4] = -Vector3<T>::dot(yaxis, eye);

		result.elements[0 + 2 * 4] = zaxis.x;
		result.elements[1 + 2 * 4] = zaxis.y;
		result.elements[2 + 2 * 4] = zaxis.z;
		result.elements[3 + 2 * 4] = -Vector3<T>::dot(zaxis, eye);

		result.elements[0 + 3 * 4] = 0;
		result.elements[1 + 3 * 4] = 0;
		result.elements[2 + 3 * 4] = 0;
		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	template<typename T>
	Matrix4<T> Matrix4<T>::transposed() const
	{
		return clone().transpose();
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::transpose()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = i + i; j < 4; j++)
			{
				std::swap(el(i, j), el(j, i));
			}
		}

		return *this;
	}

	template <typename T>
	T Matrix4<T>::determinant() const
	{
		//[a b c d]
		//[e f g h]
		//[i j k l]
		//[m n o p]
		Matrix3<T> sub1 = Matrix3<T>({
			f,g,h,
			j,k,l,
			n,o,p
		});
		Matrix3<T> sub2 = Matrix3<T>({
			g,h,e,
			k,l,i,
			o,p,m
		});
		Matrix3<T> sub3 = Matrix3<T>({
			h,e,f,
			l,i,j,
			p,m,n
		});
		Matrix3<T> sub4 = Matrix3<T>({
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
	Matrix4<T> Matrix4<T>::fromForward(const Vector3<T> & forward, const Vector3<T> & up)
	{
		Vector3<T> zaxis = forward;
		Vector3<T> xaxis = Vector3<T>::cross(up, zaxis);
		Vector3<T> yaxis = Vector3<T>::cross(zaxis, xaxis);

		Matrix4<T> result;

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
	template struct Matrix4<float>;
	template struct Matrix4<double>;
}