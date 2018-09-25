#ifndef ENTITY__CAMERA
#define ENTITY__CAMERA

#include <Tool/RenderPlane.h>

namespace Entity {

class Camera
{
public:
	Camera(const Utility::Vector3f& position, const Utility::Vector3f& lookat, const Utility::Vector3f& up, 
		   float fov, float aperture, float aspectRatio);

	Tool::Ray GetRay(const Utility::Vector2f& uv) const;
	
private:
	Tool::RenderPlane m_RenderPlane;
	Utility::Vector3f m_Position;
	float m_LensRadius = 1.0f;

};

} // namespace Entity

#endif // ENTITY__CAMERA
