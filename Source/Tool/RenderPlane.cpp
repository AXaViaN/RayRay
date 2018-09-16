#include <Tool/RenderPlane.h>

namespace Tool {

Utility::Vector3<float> m_Horizontal;
Utility::Vector3<float> m_Vertical;
RenderPlane::RenderPlane(Utility::Vector3<float> origin, Utility::Vector3<float> size, float screenRatio) : 
	m_Origin(origin),
	m_LowerLeftCorner(-size/2),
	m_Horizontal(Utility::Vector3<float>::Right * -m_LowerLeftCorner.X*2),
	m_Vertical(Utility::Vector3<float>::Up * -m_LowerLeftCorner.Y*2)
{
	// Adjust render plane with screen ratio
	m_Horizontal.X *= screenRatio;
	m_LowerLeftCorner.X *= screenRatio;
}

} // namespace Tool
