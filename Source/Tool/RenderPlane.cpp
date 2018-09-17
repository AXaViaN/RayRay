#include <Tool/RenderPlane.h>

namespace Tool {

Utility::Vector3f m_Horizontal;
Utility::Vector3f m_Vertical;
RenderPlane::RenderPlane(const Utility::Vector3f& origin, const Utility::Vector3f& size, float screenRatio) : 
	m_Origin(origin),
	m_LowerLeftCorner(-size/2),
	m_Horizontal(Utility::Vector3f::Right * -m_LowerLeftCorner.X*2),
	m_Vertical(Utility::Vector3f::Up * -m_LowerLeftCorner.Y*2)
{
	// Adjust render plane with screen ratio
	m_Horizontal.X *= screenRatio;
	m_LowerLeftCorner.X *= screenRatio;
}

} // namespace Tool