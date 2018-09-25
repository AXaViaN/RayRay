#include <Entity/Camera.h>
#include <Utility/Util.h>

namespace Entity {

static Tool::RenderPlane CreateRenderPlane(const Utility::Vector3f& position, const Utility::Vector3f& lookat, const Utility::Vector3f& up, float fov, float screenRatio);

Camera::Camera(const Utility::Vector3f& position, const Utility::Vector3f& lookat, const Utility::Vector3f& up, float fov, float screenRatio) : 
	m_RenderPlane(CreateRenderPlane(position, lookat, up, fov, screenRatio))
{
}

Tool::Ray Camera::GetRay(const Utility::Vector2f& uv) const
{
	return m_RenderPlane.GetRay(uv);
}

static Tool::RenderPlane CreateRenderPlane(const Utility::Vector3f& position, const Utility::Vector3f& lookat, const Utility::Vector3f& up, float fov, float screenRatio)
{
	float height = Utility::Tan(fov / 2.0f) * 2.0f;
	float width = height * screenRatio;

	auto planeForward = (position - lookat).Normalized();
	auto planeRight = up.Cross(planeForward).Normalized();
	auto planeUp = planeForward.Cross(planeRight).Normalized();

	Utility::Vector3f frustumSize = {width, height, 2.0f};
	return Tool::RenderPlane(position, planeForward, planeUp, planeRight, frustumSize);
}

} // namespace Entity
