#ifndef ENTITY__SCENE_OBJECT
#define ENTITY__SCENE_OBJECT

#include <Asset/Material.h>
#include <memory>

namespace Tool {
	class Ray;
	class HitResult;
}

namespace Entity {

class SceneObject
{
public:
	virtual Tool::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const = 0;

public:
	std::unique_ptr<Asset::Material> Material;

};

} // namespace Entity

#endif // ENTITY__SCENE_OBJECT
