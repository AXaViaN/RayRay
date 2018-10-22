#ifndef TOOL__HIT_RESULT
#define TOOL__HIT_RESULT

#include <Tool/Vector2.h>
#include <Tool/Vector3.h>

namespace Entity {
	class SceneObject;
}

namespace Tool {

class HitResult
{
public:
	const Entity::SceneObject* Object;

	Tool::Vector3f Point;
	Tool::Vector3f Normal;
	Tool::Vector2f UV;
	float T = 0;

	bool IsHit = false;

};

} // namespace Tool

#endif // TOOL__HIT_RESULT
