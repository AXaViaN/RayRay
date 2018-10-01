#ifndef TOOL__RAY
#define TOOL__RAY

#include <Tool/Vector3.h>

namespace Tool {

class Ray
{
public:
	inline Ray(const Tool::Vector3f& origin, const Tool::Vector3f& direction);

	inline const Tool::Vector3f& GetOrigin() const;
	inline const Tool::Vector3f& GetDirection() const;
	inline Tool::Vector3f GetPoint(float t) const;

private:
	Tool::Vector3f m_Origin;
	Tool::Vector3f m_Direction;

};

/***** IMPLEMENTATION *****/

inline Ray::Ray(const Tool::Vector3f& origin, const Tool::Vector3f& direction) : 
	m_Origin(origin),
	m_Direction(direction.Normalized())
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
inline Tool::Vector3f Ray::GetPoint(float t) const
{
	return m_Origin + m_Direction*t;
}

} // namespace Tool

#endif // TOOL__RAY
