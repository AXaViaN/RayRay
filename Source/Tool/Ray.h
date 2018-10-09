#ifndef TOOL__RAY
#define TOOL__RAY

#include <Tool/Vector3.h>

namespace Tool {

class Ray
{
public:
	inline Ray(const Tool::Vector3f& origin, const Tool::Vector3f& direction, float fireTime=0.0f);

	inline const Tool::Vector3f& GetOrigin() const;
	inline const Tool::Vector3f& GetDirection() const;
	inline const float& GetFireTime() const;

	inline Tool::Vector3f GetPoint(float t) const;

private:
	Tool::Vector3f m_Origin;
	Tool::Vector3f m_Direction;
	float m_FireTime = 0.0f;

};

/***** IMPLEMENTATION *****/

inline Ray::Ray(const Tool::Vector3f& origin, const Tool::Vector3f& direction, float time) : 
	m_Origin(origin),
	m_Direction(direction.Normalized()),
	m_FireTime(time)
{
}

inline const Tool::Vector3f& Ray::GetOrigin() const
{
	return m_Origin;
}
inline const Tool::Vector3f& Ray::GetDirection() const
{
	return m_Direction;
}
inline const float& Ray::GetFireTime() const
{
	return m_FireTime;
}

inline Tool::Vector3f Ray::GetPoint(float t) const
{
	return m_Origin + m_Direction*t;
}

} // namespace Tool

#endif // TOOL__RAY
