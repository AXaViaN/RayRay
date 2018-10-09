#include <Asset/MetalMaterial.h>
#include <Gfx/Util.h>
#include <Tool/HitResult.h>
#include <Tool/ScatterResult.h>
#include <algorithm>

namespace Asset {

MetalMaterial::MetalMaterial(const Tool::Color& color, float fuzziness) : 
	m_Color(color),
	m_Fuzziness(fuzziness)
{
	m_Fuzziness = std::clamp(m_Fuzziness, 0.0f, 1.0f);
}

Tool::ScatterResult MetalMaterial::ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const
{
	Tool::ScatterResult scatterResult;

	auto albedoColor = GetAlbedoColor({0.0f, 0.0f}, hitResult.Point);
	scatterResult.ObjectColor = {m_Color.R * albedoColor.R,
								 m_Color.G * albedoColor.G,
								 m_Color.B * albedoColor.B};

	// Reflect the ray direction and add randomness for fuzzy looks
	auto reflectedVector = Gfx::Util::Reflect(ray.GetDirection().Normalized(), hitResult.Normal);
	reflectedVector += Gfx::Util::GetRandomVectorInUnitSphere() * m_Fuzziness;
	reflectedVector.Normalize();

	scatterResult.ScatterRay = Tool::Ray(hitResult.Point, reflectedVector, ray.GetFireTime());

	scatterResult.IsScatter = (reflectedVector.Dot(hitResult.Normal) > 0);
	return scatterResult;
}

} // namespace Asset
