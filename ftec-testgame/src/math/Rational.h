#pragma once

#include "math/math.h"

namespace ftec {

	//TODO look into optimizing this shit
	//Like, really
	template <typename T>
	class Rational {
	private:
		T m_Numerator;
		T m_Denominator;
	public:
		Rational(T value) : m_Numerator(std::move(value)), m_Denominator((T)1) {};
		Rational(T numerator, T denominator) : m_Numerator(std::move(numerator)), m_Denominator(std::move(denominator)) {};

		const T &getNumerator() const { return m_Numerator; };
		const T &getDenominator() const { return m_Denominator; };

		void invert()
		{
			std::swap(m_Numerator, m_Denominator);
		}
		void optimize()
		{
			T v = ftec::gcd(m_Numerator, m_Denominator);
			if (v > 1){
				m_Numerator /= v;
				m_Denominator /= v;
			}
		}

		Rational<T> clone() const
		{
			return Rational<T>(*this);
		}

		//---------------------------------------------------------
		// Rational Rational math
		//---------------------------------------------------------
		inline Rational<T> &multiply(const Rational<T> &other)
		{
			m_Numerator *= other.m_Numerator;
			m_Denominator *= other.m_Denominator;

			return *this;
		}
		inline Rational<T> &divide(const Rational<T> &other)
		{
			m_Numerator *= other.m_Denominator;
			m_Denominator *= other.m_Numerator;

			return *this;
		}
		inline Rational<T> &add(const Rational<T> &other)
		{
			if (m_Denominator == other.m_Denominator) {
				m_Numerator += other.m_Numerator;
				return *this;
			}
			else {
				m_Numerator *= other.m_Denominator;
				m_Numerator += m_Denominator * other.m_Numerator;
				m_Denominator *= other.m_Denominator;
			}

			return *this;
		}
		inline Rational<T> &subtract(const Rational<T> &other)
		{
			if (m_Denominator == other.m_Denominator) {
				m_Numerator -= other.m_Numerator;
				return *this;
			}
			else {
				m_Numerator *= other.m_Denominator;
				m_Numerator -= m_Denominator * other.m_Numerator;
				m_Denominator *= other.m_Denominator;
			}

			return *this;
		}

		//---------------------------------------------------------
		// Rational constant math
		//---------------------------------------------------------
		inline Rational<T> &multiply(const T &other)
		{
			m_Numerator *= other;
			return *this;
		}
		inline Rational<T> &divide(const T &other)
		{
			m_Denominator *= other;
			return *this;
		}
		inline Rational<T> &add(const T &other)
		{
			m_Numerator += other * m_Denominator;
			return *this;
		}
		inline Rational<T> &subtract(const T &other)
		{
			m_Numerator -= other * m_Denominator;
			return *this;
		}

		//---------------------------------------------------------
		// Rational Rational operators
		//---------------------------------------------------------
		Rational<T> operator+(const Rational<T> &other) const { return clone().add(other); };
		Rational<T> operator-(const Rational<T> &other) const { return clone().subtract(other); };
		Rational<T> operator/(const Rational<T> &other) const { return clone().divide(other); };
		Rational<T> operator*(const Rational<T> &other) const { return clone().multiply(other); };

		Rational<T> &operator+=(const Rational<T> &other) { return add(other); };
		Rational<T> &operator-=(const Rational<T> &other) { return subtract(other); };
		Rational<T> &operator/=(const Rational<T> &other) { return divide(other); };
		Rational<T> &operator*=(const Rational<T> &other) { return multiply(other); };


		//---------------------------------------------------------
		// Rational constant operators
		//---------------------------------------------------------
		Rational<T> operator+(const T &other) const { return clone().add(other); };
		Rational<T> operator-(const T &other) const { return clone().subtract(other); };
		Rational<T> operator/(const T &other) const { return clone().divide(other); };
		Rational<T> operator*(const T &other) const { return clone().multiply(other); };

		Rational<T> &operator+=(const T &other) { return add(other); };
		Rational<T> &operator-=(const T &other) { return subtract(other); };
		Rational<T> &operator/=(const T &other) { return divide(other); };
		Rational<T> &operator*=(const T &other) { return multiply(other); };


		//---------------------------------------------------------
		// Rational Rational compare
		//---------------------------------------------------------
		bool operator==(const Rational<T> &other) const { return m_Numerator == other.m_Numerator && m_Denominator == other.m_Denominator; };

		//---------------------------------------------------------
		// Rational constant compare
		//---------------------------------------------------------
		bool operator==(const T &other) const { return m_Numerator == other && (m_Denominator == m_Numerator || m_Numerator == 0); };
	};

	typedef Rational<int> Rationali;
}