#ifndef ENTITY__SCENE
#define ENTITY__SCENE

#include <Entity/Sphere.h>
#include <vector>

namespace Entity {

struct Scene
{
	std::vector<Entity::Sphere> SphereList;
};

} // namespace Entity

#endif // ENTITY__SCENE

