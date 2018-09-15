#ifndef UTILITY__RAY
#define UTILITY__RAY

#include <Utility/Vector3.h>

namespace Utility {

class Ray
{
public:
	inline Ray(const Utility::Vector3<float>& origin, const Utility::Vector3<float>& direction);

	inline const Utility::Vector3<float>& GetOrigin() const;
	inline const Utility::Vector3<float>& GetDirection() const;
	inline Utility::Vector3<float> GetPoint(float t) const;

private:
	Utility::Vector3<float> m_Origin;
	Utility::Vector3<float> m_Direction;

};

inline Ray::Ray(const Utility::Vector3<float>& origin, const Utility::Vector3<float>& direction) : 
	m_Origin(origin),
	m_Direction(direction)
{
}

inline const Utility::Vector3<float>& Ray::GetOrigin() const
{
	return m_Origin;
}
inline const Utility::Vector3<float>& Ray::GetDirection() const
{
	return m_Direction;
}
inline Utility::Vector3<float> Ray::GetPoint(float t) const
{
	return m_Origin + m_Direction*t;
}

} // namespace Utility

#endif // UTILITY__RAY
