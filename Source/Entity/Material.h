#ifndef ENTITY__MATERIAL
#define ENTITY__MATERIAL

#include <Tool/Ray.h>
#include <Utility/Color.h>
#include <Utility/HitResult.h>
#include <Utility/ScatterResult.h>

namespace Entity {

class Material
{
public:
	virtual Utility::ScatterResult ScatterCheck(const Tool::Ray& ray, const Utility::HitResult& hitResult) const = 0;

};

} // namespace Entity

#endif // ENTITY__MATERIAL
