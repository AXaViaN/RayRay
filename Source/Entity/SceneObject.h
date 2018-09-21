#ifndef ENTITY__SCENE_OBJECT
#define ENTITY__SCENE_OBJECT

#include <Entity/Material.h>
#include <Tool/Ray.h>
#include <Utility/Color.h>
#include <Utility/HitResult.h>
#include <memory>

namespace Entity {

class SceneObject
{
public:
	virtual Utility::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const = 0;

public:
	std::unique_ptr<Entity::Material> Material;

};

} // namespace Entity

#endif // ENTITY__SCENE_OBJECT
