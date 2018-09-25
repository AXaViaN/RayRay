#include <Entity/Camera.h>
#include <Utility/Util.h>

namespace Entity {

static Tool::RenderPlane CreateRenderPlane(const Utility::Vector3f& forward, const Utility::Vector3f& up, float fov, float aspectRatio);

Camera::Camera(const Utility::Vector3f& position, const Utility::Vector3f& lookat, const Utility::Vector3f& up, float fov, float aperture, float aspectRatio) : 
	m_RenderPlane(CreateRenderPlane(position-lookat, up, fov, aspectRatio)),
	m_Position(position),
	m_LensRadius(aperture / 2.0f)
{
}

Tool::Ray Camera::GetRay(const Utility::Vector2f& uv) const
{
	auto rayDirection = m_RenderPlane.GetPoint(uv);

	auto randomLensDirection = Utility::GetRandomVectorInUnitDisk() * m_LensRadius;
	auto offset = m_RenderPlane.Right * randomLensDirection.X + 
				  m_RenderPlane.Up    * randomLensDirection.Y;

	return Tool::Ray(m_Position+offset, rayDirection-offset);
}

static Tool::RenderPlane CreateRenderPlane(const Utility::Vector3f& forward, const Utility::Vector3f& up, float fov, float aspectRatio)
{
	float height = Utility::Tan(fov / 2.0f) * 2.0f;
	float width = height * aspectRatio;
	Utility::Vector3f frustumSize = {width, height, 2.0f};

	float focusDistance = forward.Length();
	frustumSize *= focusDistance;

	auto cameraUp = up.Normalized();
	auto planeForward = forward.Normalized();
	auto planeRight = cameraUp.Cross(planeForward).Normalized();
	auto planeUp = planeForward.Cross(planeRight).Normalized();

	return Tool::RenderPlane(planeForward, planeUp, planeRight, frustumSize);
}

} // namespace Entity
