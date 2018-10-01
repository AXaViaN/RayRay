#ifndef ENTITY__CAMERA
#define ENTITY__CAMERA

#include <Gfx/RenderPlane.h>
#include <Tool/Vector3.h>

namespace Tool {
	class Ray;
}

namespace Entity {

class Camera
{
public:
	Camera(const Tool::Vector3f& position, const Tool::Vector3f& lookat, const Tool::Vector3f& up, 
		   float fov, float aperture, float focalOffset, float aspectRatio);

	Tool::Ray GetRay(const Tool::Vector2f& uv) const;
	
private:
	Gfx::RenderPlane m_RenderPlane;
	Tool::Vector3f m_Position;
	float m_LensRadius = 1.0f;

};

} // namespace Entity

#endif // ENTITY__CAMERA
