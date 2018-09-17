#ifndef ENTITY__SPHERE
#define ENTITY__SPHERE

#include <Utility/Vector3.h>
#include <Utility/Color.h>

namespace Entity {

struct Sphere
{
	Utility::Color Color;

	Utility::Vector3f Center;
	float Radius = 1.0f;
};

} // namespace Entity

#endif // ENTITY__SPHERE
