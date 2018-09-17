#ifndef UTILITY__RAY
#define UTILITY__RAY

#include <Utility/Vector3.h>

namespace Utility {

class Ray
{
public:
	inline Ray(const Utility::Vector3f& origin, const Utility::Vector3f& direction);

	inline const Utility::Vector3f& GetOrigin() const;
	inline const Utility::Vector3f& GetDirection() const;
	inline Utility::Vector3f GetPoint(float t) const;

private:
	Utility::Vector3f m_Origin;
	Utility::Vector3f m_Direction;

};

inline Ray::Ray(const Utility::Vector3f& origin, const Utility::Vector3f& direction) : 
	m_Origin(origin),
	m_Direction(direction)
{
}

inline const Utility::Vector3f& Ray::GetOrigin() const
{
	return m_Origin;
}
inline const Utility::Vector3f& Ray::GetDirection() const
{
	return m_Direction;
}
inline Utility::Vector3f Ray::GetPoint(float t) const
{
	return m_Origin + m_Direction*t;
}

} // namespace Utility

#endif // UTILITY__RAY
