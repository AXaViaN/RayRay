#include <Gfx/RenderPlane.h>

namespace Gfx {

RenderPlane::RenderPlane(const Tool::Vector3f& forward, const Tool::Vector3f& up, const Tool::Vector3f& right, const Tool::Vector3f& frustumSize) : 
	Up(up.Normalized()),
	Right(right.Normalized()),
	Forward(forward.Normalized()),
	m_Horizontal(Right * frustumSize.X),
	m_Vertical(Up * frustumSize.Y),
	m_LowerLeftCorner(- m_Horizontal/2 - m_Vertical/2 - (Forward*frustumSize.Z)/2.0f)
{
}

Tool::Vector3f RenderPlane::GetPoint(const Tool::Vector2f& uv) const
{
	return (m_LowerLeftCorner + m_Horizontal*uv.X + m_Vertical*uv.Y);
}

} // namespace Gfx
