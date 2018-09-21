#include <Entity/MetalMaterial.h>
#include <Utility/Util.h>

namespace Entity {

Utility::ScatterResult MetalMaterial::ScatterCheck(const Tool::Ray& ray, const Utility::HitResult& hitResult) const
{
	Utility::ScatterResult scatterResult;
	scatterResult.Color = m_Color;

	// Reflect the ray direction and add randomness for fuzzy looks
	auto reflectedVector = Utility::Reflect(ray.GetDirection().Normalized(), hitResult.Normal);
	reflectedVector += Utility::GetRandomVectorInUnitSphere() * m_Fuzziness;

	scatterResult.ReflectionRay = Tool::Ray(hitResult.Point, reflectedVector.Normalized());

	scatterResult.IsScatter = (reflectedVector.Dot(hitResult.Normal) > 0);
	return scatterResult;
}

} // namespace Entity
