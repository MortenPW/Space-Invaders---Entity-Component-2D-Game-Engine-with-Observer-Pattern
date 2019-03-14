#ifndef VECTOR2D
#define VECTOR2D
#include <cmath>

namespace game 
{
	template <class T>
	class Vector2D
	{
	public:
		// None explicit for conversion
		Vector2D();
		Vector2D(T x, T y);

		Vector2D operator+(const Vector2D& v2) const;
		Vector2D operator+=(const Vector2D& v2);
		Vector2D operator-(const Vector2D& v2) const;
		Vector2D operator-=(const Vector2D& v2);
		Vector2D operator*(T scalar) const;
		Vector2D operator*=(T scalar);
		Vector2D operator/(T scalar) const;
		Vector2D operator/=(T scalar);

		T x() const;
		T y() const;
		T length() const;
		void set_x(T x);
		void set_y(T y);
		void normalize();

	private:
		T x_;
		T y_;
	};

	template <class T>
	Vector2D<T>::Vector2D(): x_(0), y_(0)
	{
	}

	template <class T>
	Vector2D<T>::Vector2D(const T x, const T y)
	{
		x_ = x;
		y_ = y;
	}

	template <class T>
	Vector2D<T> Vector2D<T>::operator+(const Vector2D& v2) const
	{
		return Vector2D(x_ + v2.x_, y_ + v2.y_);
	}

	template <class T>
	Vector2D<T> Vector2D<T>::operator+=(const Vector2D& v2)
	{
		x_ += v2.x_;
		y_ += v2.y_;

		return *this; // we return the self object
	}

	template <class T>
	Vector2D<T> Vector2D<T>::operator-(const Vector2D& v2) const
	{
		return Vector2D(x_ - v2.x_, y_ - v2.y_);
	}

	template <class T>
	Vector2D<T> Vector2D<T>::operator-=(const Vector2D& v2)
	{
		x_ -= v2.x_;
		y_ -= v2.y_;

		return *this;
	}

	template <class T>
	Vector2D<T> Vector2D<T>::operator*(const T scalar) const
	{
		return Vector2D(x_ * scalar, y_ * scalar);
	}

	template <class T>
	Vector2D<T> Vector2D<T>::operator*=(const T scalar)
	{
		x_ *= scalar;
		y_ *= scalar;

		return *this;
	}

	template <class T>
	Vector2D<T> Vector2D<T>::operator/(const T scalar) const
	{
		return Vector2D(x_ / scalar, y_ / scalar);
	}

	template <class T>
	Vector2D<T> Vector2D<T>::operator/=(const T scalar)
	{
		x_ /= scalar;
		y_ /= scalar;

		return *this;
	}

	template <class T>
	T Vector2D<T>::x() const
	{
		return x_;
	}

	template <class T>
	T Vector2D<T>::y() const
	{
		return y_;
	}

	template <class T>
	T Vector2D<T>::length() const
	{
		return std::sqrt(x_ * x_ + y_ * y_);
	}

	template <class T>
	void Vector2D<T>::set_x(const T x)
	{
		x_ = x;
	}

	template <class T>
	void Vector2D<T>::set_y(const T y)
	{
		y_ = y;
	}

	template <class T>
	void Vector2D<T>::normalize()
	{
		const auto aux_length = length();
		if (aux_length > 0) //don't divide 0!
		{
			(*this) *= 1 / aux_length;
		}
	}
}

#endif