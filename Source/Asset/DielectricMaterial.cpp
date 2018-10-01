#include <Asset/DielectricMaterial.h>
#include <Gfx/Util.h>
#include <Tool/HitResult.h>
#include <Tool/ScatterResult.h>
#include <Tool/Random.h>

namespace Asset {

DielectricMaterial::DielectricMaterial(float refractiveIndex) : 
	m_RefractiveIndex(refractiveIndex)
{
}

Tool::ScatterResult DielectricMaterial::ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const
{
	Tool::ScatterResult scatterResult;
	scatterResult.ObjectColor = {1.0f, 1.0f, 1.0f};
	scatterResult.IsScatter = true;

	// We want to refract. So we are calculating from air to inside of the material
	Tool::Vector3f outwardNormal = hitResult.Normal;
	float N1OverN2 = 1.0f / m_RefractiveIndex;
	float cosine = ray.GetDirection().Dot(hitResult.Normal);

	// If we are already inside and refracting from inside of the material to air
	if(cosine > 0)
	{
		outwardNormal = -hitResult.Normal;
		N1OverN2 = m_RefractiveIndex;
		cosine *= -m_RefractiveIndex;
	}

	// Calculate fresnel (reflection coefficient)
	// If a refraction is not possible we will take fresnel as 1 and reflect
	float fresnel = 1.0f;
	Tool::Vector3f refracted = Gfx::Util::Refract(ray.GetDirection(), outwardNormal, N1OverN2);
	if(refracted.SquaredLength() != 0)
	{
		fresnel = Gfx::Util::FresnelSchlick(-cosine, m_RefractiveIndex);
	}

	// Select a random barrier and test fresnel
	float fresnelBarrier = Tool::Random::Instance().GetFloat();
	if(fresnel < fresnelBarrier)
	{
		scatterResult.ScatterRay = Tool::Ray(hitResult.Point, refracted);
	}
	else
	{
		Tool::Vector3f reflected = Gfx::Util::Reflect(ray.GetDirection(), hitResult.Normal);
		scatterResult.ScatterRay = Tool::Ray(hitResult.Point, reflected);
	}

	return scatterResult;
}

} // namespace Asset
