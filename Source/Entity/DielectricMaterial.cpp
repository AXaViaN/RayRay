#include <Entity/DielectricMaterial.h>
#include <Utility/Util.h>
#include <Utility/Random.h>

namespace Entity {

static Utility::Random s_Random;

Utility::ScatterResult DielectricMaterial::ScatterCheck(const Tool::Ray& ray, const Utility::HitResult& hitResult) const
{
	Utility::ScatterResult scatterResult;
	scatterResult.ObjectColor = {1.0f, 1.0f, 1.0f};
	scatterResult.IsScatter = true;

	// We want to refract. So we are calculating from air to inside of the material
	Utility::Vector3f outwardNormal = hitResult.Normal;
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
	Utility::Vector3f refracted = Utility::Refract(ray.GetDirection(), outwardNormal, N1OverN2);
	if(refracted.SquaredLength() != 0)
	{
		fresnel = Utility::FresnelSchlick(-cosine, m_RefractiveIndex);
	}

	// Select a random barrier and test fresnel
	float fresnelBarrier = s_Random.GetFloat();
	if(fresnel < fresnelBarrier)
	{
		scatterResult.ScatterRay = Tool::Ray(hitResult.Point, refracted);
	}
	else
	{
		Utility::Vector3f reflected = Utility::Reflect(ray.GetDirection(), hitResult.Normal);
		scatterResult.ScatterRay = Tool::Ray(hitResult.Point, reflected);
	}

	return scatterResult;
}

} // namespace Entity
