#ifndef ASSET__DIELECTRIC_MATERIAL
#define ASSET__DIELECTRIC_MATERIAL

#include <Asset/Material.h>

namespace Asset {

class DielectricMaterial : public Asset::Material
{
public:
	DielectricMaterial(float refractiveIndex);

	virtual Tool::ScatterResult ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const override;

private:
	float m_RefractiveIndex = 0.0f;

};

} // namespace Asset

#endif // ASSET__DIELECTRIC_MATERIAL
