#ifndef TOOL__AABB
#define TOOL__AABB

#include <Tool/Vector3.h>

namespace Tool {
	class Ray;
}

namespace Tool {

class AABB
{
public:
	inline AABB();
	inline AABB(const Tool::Vector3f& min, const Tool::Vector3f& max);
	AABB(const AABB& box1, const AABB& box2);

	bool Hit(const Tool::Ray& ray, float minT, float maxT) const;

	inline bool IsSmallerOnAxis(const AABB& other, int axisIdx) const;

private:
	Tool::Vector3f m_Min;
	Tool::Vector3f m_Max;

};

/***** IMPLEMENTATION *****/

inline AABB::AABB()
{
}
inline AABB::AABB(const Tool::Vector3f& min, const Tool::Vector3f& max) : 
	m_Min(min),
	m_Max(max)
{
}

inline bool AABB::IsSmallerOnAxis(const AABB& other, int axisIdx) const
{
	return m_Min[axisIdx] < other.m_Min[axisIdx];
}

} // namespace Tool

#endif // TOOL__AABB
