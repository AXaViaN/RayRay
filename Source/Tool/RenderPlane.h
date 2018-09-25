#ifndef TOOL__RENDER_PLANE
#define TOOL__RENDER_PLANE

#include <Tool/Ray.h>
#include <Utility/Vector3.h>
#include <Utility/Vector2.h>

namespace Tool {

class RenderPlane
{
public:
	RenderPlane(const Utility::Vector3f& forward, const Utility::Vector3f& up, const Utility::Vector3f& right, const Utility::Vector3f& frustumSize);

	Utility::Vector3f GetPoint(const Utility::Vector2f& uv) const;

public:
	const Utility::Vector3f Up;
	const Utility::Vector3f Right;
	const Utility::Vector3f Forward;

private:
	Utility::Vector3f m_Horizontal;
	Utility::Vector3f m_Vertical;
	Utility::Vector3f m_LowerLeftCorner;

};

} // namespace Tool

#endif // TOOL__RENDER_PLANE
