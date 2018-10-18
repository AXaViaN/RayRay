#include <Tool/AABB.h>
#include <Tool/Math.h>
#include <Tool/Ray.h>
#include <algorithm>

namespace Tool {

AABB::AABB(const AABB& box1, const AABB& box2) : 
	m_Min(Tool::Math::Min(box1.m_Min.X, box2.m_Min.X),
		  Tool::Math::Min(box1.m_Min.Y, box2.m_Min.Y),
		  Tool::Math::Min(box1.m_Min.Z, box2.m_Min.Z)),

	m_Max(Tool::Math::Max(box1.m_Max.X, box2.m_Max.X),
		  Tool::Math::Max(box1.m_Max.Y, box2.m_Max.Y),
		  Tool::Math::Max(box1.m_Max.Z, box2.m_Max.Z))
{
	// SurroundingBox of box1 and box2
}

bool AABB::Hit(const Tool::Ray& ray, float minT, float maxT) const
{
	for( int i=0 ; i<3 ; ++i )
	{
		// P(t) = O + D*t
		// P(t) is AABB's point, O is ray origin, D is ray direction
		// We need interaction point which is t
		// t = (P(t) - O) / D

		//       t0 |      t1 |
		//        \ |       \ |
		//         \|        \|
		// x--------|---------|------> ray
		//          |         |
		//          |         |
		//      AABB_Min  AABB_Max
		
		float t0 = (m_Min[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i];
		float t1 = (m_Max[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i];

		// t0 is always smaller
		if(t0 > t1)
		{
			std::swap(t0, t1);
		}

		// Select biggest minT and smallest maxT
		minT = Tool::Math::Max(minT, t0);
		maxT = Tool::Math::Min(maxT, t1);

		// If min is bigger, interactions don't overlap (ray missed the AABB)
		if(minT >= maxT)
		{
			return false;
		}
	}

	return true;
}

} // namespace Tool
