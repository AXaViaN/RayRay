#include <Entity/Camera.h>
#include <Gfx/Util.h>
#include <Tool/Math.h>
#include <Tool/Ray.h>

namespace Entity {

static Gfx::RenderPlane CreateRenderPlane(const Tool::Vector3f& forward, const Tool::Vector3f& up, float fov, float focalOffset, float aspectRatio);

Camera::Camera(const Tool::Vector3f& position, const Tool::Vector3f& lookat, const Tool::Vector3f& up, float fov, float aperture, float focalOffset, float aspectRatio) : 
	m_RenderPlane(CreateRenderPlane(position-lookat, up, fov, focalOffset, aspectRatio)),
	m_Position(position),
	m_LensRadius(aperture / 2.0f)
{
}

Tool::Ray Camera::GetRay(const Tool::Vector2f& uv) const
{
	auto rayDirection = m_RenderPlane.GetPoint(uv);

	auto randomLensDirection = Gfx::Util::GetRandomVectorInUnitDisk() * m_LensRadius;
	auto offset = m_RenderPlane.Right * randomLensDirection.X + 
				  m_RenderPlane.Up    * randomLensDirection.Y;

	return Tool::Ray(m_Position+offset, rayDirection-offset);
}

/***** STATIC FUNCTION *****/

static Gfx::RenderPlane CreateRenderPlane(const Tool::Vector3f& forward, const Tool::Vector3f& up, float fov, float focalOffset, float aspectRatio)
{
	float height = Tool::Math::Tan(fov / 2.0f) * 2.0f;
	float width = height * aspectRatio;
	Tool::Vector3f frustumSize = {width, height, 2.0f};

	float focalLength = forward.Length() + focalOffset;
	frustumSize *= focalLength;

	auto cameraUp = up.Normalized();
	auto planeForward = forward.Normalized();
	auto planeRight = cameraUp.Cross(planeForward).Normalized();
	auto planeUp = planeForward.Cross(planeRight).Normalized();

	return Gfx::RenderPlane(planeForward, planeUp, planeRight, frustumSize);
}

} // namespace Entity
