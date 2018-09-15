#ifndef UTILITY__VECTOR3
#define UTILITY__VECTOR3

#include <cmath>

namespace Utility {

template<typename T> class Vector3
{
public:
	inline Vector3();
	inline Vector3(T x, T y, T z);

	inline T Dot(const Vector3& other) const;
	inline Vector3 Cross(const Vector3& other) const;
	inline T Length() const;
	inline T SquaredLength() const;
	inline void Normalize();
	inline Vector3 Normalized() const;
	
	inline T operator[](int i) const;
	inline T& operator[](int i);
	inline const Vector3& operator+() const;
	inline Vector3 operator-() const;

	inline Vector3 operator+(const Vector3& other) const;
	inline Vector3 operator-(const Vector3& other) const;
	inline Vector3 operator*(const Vector3& other) const;
	inline Vector3 operator/(const Vector3& other) const;
	inline Vector3 operator*(T t) const;
	inline Vector3 operator/(T t) const;

	inline Vector3& operator+=(const Vector3& other);
	inline Vector3& operator-=(const Vector3& other);
	inline Vector3& operator*=(const Vector3& other);
	inline Vector3& operator/=(const Vector3& other);
	inline Vector3& operator*=(T t);
	inline Vector3& operator/=(T t);

public:
	T X = 0;
	T Y = 0;
	T Z = 0;

};

template<typename T> inline Vector3<T>::Vector3()
{
}
template<typename T> inline Vector3<T>::Vector3(T x, T y, T z) : 
	X(x),
	Y(y),
	Z(z)
{
}

template<typename T> inline T Vector3<T>::Dot(const Vector3<T>& other) const
{
	return X*other.X + Y*other.Y + Z*other.Z;
}
template<typename T> inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& other) const
{
	return { Y*other.Z - Z*other.Y,
			-X*other.Z - Z*other.X,
			 X*other.Y - Y*other.X};
}
template<typename T> inline T Vector3<T>::Length() const
{
	auto squaredLength = static_cast<double>(SquaredLength());
	return static_cast<T>(std::sqrt(squaredLength));
}
template<typename T> inline T Vector3<T>::SquaredLength() const
{
	return X*X + Y*Y + Z*Z;
}
template<typename T> inline void Vector3<T>::Normalize()
{
	*this = Normalized();
}
template<typename T> inline Vector3<T> Vector3<T>::Normalized() const
{
	return *this / Length();
}

template<typename T> inline T Vector3<T>::operator[](int i) const
{
	return i==0 ? X : (i==1 ? Y : Z);
}
template<typename T> inline T& Vector3<T>::operator[](int i)
{
	return i==0 ? X : (i==1 ? Y : Z);
}
template<typename T> inline const Vector3<T>& Vector3<T>::operator+() const
{
	return *this;
}
template<typename T> inline Vector3<T> Vector3<T>::operator-() const
{
	return {-X, -Y, -Z};
}

template<typename T> inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const
{
	return {X+other.X, Y+other.Y, Z+other.Z};
}
template<typename T> inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& other) const
{
	return {X-other.X, Y-other.Y, Z-other.Z};
}
template<typename T> inline Vector3<T> Vector3<T>::operator*(const Vector3<T>& other) const
{
	return {X*other.X, Y*other.Y, Z*other.Z};
}
template<typename T> inline Vector3<T> Vector3<T>::operator/(const Vector3<T>& other) const
{
	return {X/other.X, Y/other.Y, Z/other.Z};
}
template<typename T> inline Vector3<T> Vector3<T>::operator*(T t) const
{
	return {X*t, Y*t, Z*t};
}
template<typename T> inline Vector3<T> Vector3<T>::operator/(T t) const
{
	return {X/t, Y/t, Z/t};
}

template<typename T> inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& other)
{
	*this = *this + other;
	return *this;
}
template<typename T> inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& other)
{
	*this = *this - other;
	return *this;
}
template<typename T> inline Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& other)
{
	*this = *this * other;
	return *this;
}
template<typename T> inline Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& other)
{
	*this = *this / other;
	return *this;
}
template<typename T> inline Vector3<T>& Vector3<T>::operator*=(T t)
{
	*this = *this * t;
	return *this;
}
template<typename T> inline Vector3<T>& Vector3<T>::operator/=(T t)
{
	*this = *this / t;
	return *this;
}

} // namespace Utility

#endif // UTILITY__VECTOR3
