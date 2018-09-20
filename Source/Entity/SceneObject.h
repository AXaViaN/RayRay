#ifndef ENTITY__SCENE_OBJECT
#define ENTITY__SCENE_OBJECT

#include <Tool/Ray.h>
#include <Utility/Color.h>
#include <Utility/HitResult.h>

namespace Entity {

class SceneObject
{
public:
	virtual Utility::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const = 0;

public:
	Utility::Color Color;
	float Absorption = 0.0f;

};

} // namespace Entity

#endif // ENTITY__SCENE_OBJECT
