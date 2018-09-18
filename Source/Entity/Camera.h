#ifndef ENTITY__CAMERA
#define ENTITY__CAMERA

#include <Tool/RenderPlane.h>
#include <Tool/Ray.h>
#include <Utility/Vector2.h>

namespace Entity {

class Camera
{
public:
	Camera(const Utility::Vector3f& position, float screenRatio);

	Tool::Ray GetRay(const Utility::Vector2f uv) const;
	
private:
	Tool::RenderPlane m_RenderPlane;
	Utility::Vector3f m_Position;

};

} // namespace Entity

#endif // ENTITY__CAMERA
