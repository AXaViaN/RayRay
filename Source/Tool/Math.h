#ifndef TOOL__MATH
#define TOOL__MATH

#include <cmath>

namespace Tool {

class Math
{
public:
	static inline float Pi();
	static inline float ToRadian(float angle);

	static inline float Sin(float angle);
	static inline float Cos(float angle);
	static inline float Tan(float angle);

};

/***** IMPLEMENTATION *****/

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

} // namespace Tool

#endif // TOOL__MATH
