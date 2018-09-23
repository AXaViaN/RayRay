#include <Entity/LambertianMaterial.h>
#include <Utility/Util.h>

namespace Entity {

Utility::ScatterResult LambertianMaterial::ScatterCheck(const Tool::Ray& ray, const Utility::HitResult& hitResult) const
{
	Utility::ScatterResult scatterResult;
	scatterResult.ObjectColor = m_Color;

	// Select a random reflection direction
	auto target = hitResult.Point + hitResult.Normal + Utility::GetRandomVectorInUnitSphere();
	auto targetDirection = (target - hitResult.Point).Normalized();

	scatterResult.ScatterRay = Tool::Ray(hitResult.Point, targetDirection);
	
	scatterResult.IsScatter = true;
	return scatterResult;
}

} // namespace Entity
