#ifndef TOOL__MATH
#define TOOL__MATH

#include <cmath>

namespace Tool {

class Math
{
public:
	template<typename T> static inline T Abs(const T& value);
	template<typename T> static inline T Min(const T& value1, const T& value2);
	template<typename T> static inline T Max(const T& value1, const T& value2);

	static inline float Pi();
	static inline float ToRadian(float angle);
	static inline float ToAngle(float radian);

	static inline float Sin(float angle);
	static inline float Cos(float angle);
	static inline float Tan(float angle);
	static inline float SinRadian(float radian);
	static inline float CosRadian(float radian);
	static inline float TanRadian(float radian);
	static inline float ArcSin(float x);
	static inline float ArcCos(float x);
	static inline float ArcTan(float x);
	static inline float ArcTan(float y, float x);

	template<typename T> static inline T Percentage(const T& start, const T& end, const T& value);
	template<typename T> static inline T Lerp(const T& start, const T& end, float percentage);

};

/***** IMPLEMENTATION *****/

template<typename T> inline T Math::Abs(const T& value)
{
	return std::abs(value);
}
template<typename T> inline T Math::Min(const T& value1, const T& value2)
{
	return (value1 < value2) ? value1 : value2;
}
template<typename T> inline T Math::Max(const T& value1, const T& value2)
{
	return (value1 > value2) ? value1 : value2;
}

inline float Math::Pi()
{
	static const float pi = std::acosf(-1.0f);
	return pi;
}
inline float Math::ToRadian(float angle)
{
	static const float factor = Pi() / 180.0f;
	return angle * factor;
}
inline float Math::ToAngle(float radian)
{
	static const float factor = Pi() / 180.0f;
	return radian / factor;
}

inline float Math::Sin(float angle)
{
	return std::sinf(ToRadian(angle));
}
inline float Math::Cos(float angle)
{
	return std::cosf(ToRadian(angle));
}
inline float Math::Tan(float angle)
{
	return std::tanf(ToRadian(angle));
}
inline float Math::SinRadian(float radian)
{
	return std::sinf(radian);
}
inline float Math::CosRadian(float radian)
{
	return std::cosf(radian);
}
inline float Math::TanRadian(float radian)
{
	return std::tanf(radian);
}
inline float Math::ArcSin(float x)
{
	return ToAngle(std::asin(x));
}
inline float Math::ArcCos(float x)
{
	return ToAngle(std::acos(x));
}
inline float Math::ArcTan(float x)
{
	return ToAngle(std::atan(x));
}
inline float Math::ArcTan(float y, float x)
{
	return ToAngle(std::atan2(y, x));
}

template<typename T> inline T Math::Percentage(const T& start, const T& end, const T& value)
{
	return (value - start) / (end - start);
}
template<typename T> inline T Math::Lerp(const T& start, const T& end, float percentage)
{
	return start + ((end - start) * percentage);
}

} // namespace Tool

#endif // TOOL__MATH
