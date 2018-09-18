#include <Entity/Camera.h>

namespace Entity {

Camera::Camera(const Utility::Vector3f& position, float screenRatio) : 
	m_RenderPlane(position, {1.0f, 1.0f, 1.0f}, screenRatio),
	m_Position(position)
{
}

Tool::Ray Camera::GetRay(const Utility::Vector2f uv) const
{
	auto rayHead = m_RenderPlane.GetLowerLeft() + 
				   m_RenderPlane.GetHorizontal()*uv.X + m_RenderPlane.GetVertical()*uv.Y;
	auto rayDirection = rayHead - m_Position;

	return Tool::Ray(m_Position, rayDirection);
}

} // namespace Entity
