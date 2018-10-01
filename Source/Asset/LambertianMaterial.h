#ifndef ASSET__LAMBERTIAN_MATERIAL
#define ASSET__LAMBERTIAN_MATERIAL

#include <Asset/Material.h>
#include <Tool/Color.h>

namespace Asset {

class LambertianMaterial : public Asset::Material
{
public:
	LambertianMaterial(const Tool::Color& color);

	virtual Tool::ScatterResult ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const override;

private:
	Tool::Color m_Color;

};

} // namespace Asset

#endif // ASSET__LAMBERTIAN_MATERIAL
