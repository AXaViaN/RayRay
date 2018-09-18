#ifndef UTILITY__HIT_RESULT
#define UTILITY__HIT_RESULT

#include <Utility/Vector3.h>

namespace Entity {
class SceneObject;
}

namespace Utility {

struct HitResult
{
	const Entity::SceneObject* Object;

	Utility::Vector3f Point;
	Utility::Vector3f Normal;
	float T = 0;

	bool IsHit = false;
};

} // namespace Utility

#endif // UTILITY__HIT_RESULT
