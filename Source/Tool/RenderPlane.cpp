#include <Tool/RenderPlane.h>

namespace Tool {

RenderPlane::RenderPlane(const Utility::Vector3f& forward, const Utility::Vector3f& up, const Utility::Vector3f& right, const Utility::Vector3f& frustumSize) : 
	Up(up.Normalized()),
	Right(right.Normalized()),
	Forward(forward.Normalized()),
	m_Horizontal(Right * frustumSize.X),
	m_Vertical(Up * frustumSize.Y),
	m_LowerLeftCorner(- m_Horizontal/2 - m_Vertical/2 - (Forward*frustumSize.Z)/2.0f)
{
}

Utility::Vector3f RenderPlane::GetPoint(const Utility::Vector2f& uv) const
{
	return (m_LowerLeftCorner + m_Horizontal*uv.X + m_Vertical*uv.Y);
}

} // namespace Tool
