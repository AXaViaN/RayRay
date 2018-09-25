#ifndef ENTITY__CAMERA
#define ENTITY__CAMERA

#include <Tool/RenderPlane.h>

namespace Entity {

class Camera
{
public:
	Camera(const Utility::Vector3f& position, const Utility::Vector3f& lookat, const Utility::Vector3f& up, 
		   float fov, float screenRatio);

	Tool::Ray GetRay(const Utility::Vector2f& uv) const;
	
private:
	Tool::RenderPlane m_RenderPlane;

};

} // namespace Entity

#endif // ENTITY__CAMERA
