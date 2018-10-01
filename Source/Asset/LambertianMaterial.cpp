#include <Asset/LambertianMaterial.h>
#include <Gfx/Util.h>
#include <Tool/HitResult.h>
#include <Tool/ScatterResult.h>

namespace Asset {

LambertianMaterial::LambertianMaterial(const Tool::Color& color) : 
	m_Color(color)
{
}

Tool::ScatterResult LambertianMaterial::ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const
{
	Tool::ScatterResult scatterResult;
	scatterResult.ObjectColor = m_Color;

	// Select a random reflection direction
	auto target = hitResult.Point + hitResult.Normal + Gfx::Util::GetRandomVectorInUnitSphere();
	auto targetDirection = (target - hitResult.Point).Normalized();

	scatterResult.ScatterRay = Tool::Ray(hitResult.Point, targetDirection);
	
	scatterResult.IsScatter = true;
	return scatterResult;
}

} // namespace Asset
