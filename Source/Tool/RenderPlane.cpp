#include <Tool/RenderPlane.h>

namespace Tool {

RenderPlane::RenderPlane(const Utility::Vector3f& position, const Utility::Vector3f& forward, const Utility::Vector3f& up, const Utility::Vector3f& right, const Utility::Vector3f& frustumSize) : 
	m_Position(position),
	m_Horizontal(right.Normalized() * frustumSize.X),
	m_Vertical(up.Normalized() * frustumSize.Y),
	m_LowerLeftCorner(position - m_Horizontal/2 - m_Vertical/2 - forward)
{
}

Tool::Ray RenderPlane::GetRay(const Utility::Vector2f& uv) const
{
	auto rayHead = m_LowerLeftCorner + m_Horizontal*uv.X + m_Vertical*uv.Y;
	auto rayDirection = rayHead - m_Position;

	return Tool::Ray(m_Position, rayDirection);
}

} // namespace Tool
