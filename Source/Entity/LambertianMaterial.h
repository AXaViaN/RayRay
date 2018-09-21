#ifndef ENTITY__LAMBERTIAN_MATERIAL
#define ENTITY__LAMBERTIAN_MATERIAL

#include <Entity/Material.h>

namespace Entity {

class LambertianMaterial : public Entity::Material
{
public:
	inline LambertianMaterial(const Utility::Color& color);

	virtual Utility::ScatterResult ScatterCheck(const Tool::Ray& ray, const Utility::HitResult& hitResult) const override;

private:
	Utility::Color m_Color;

};

inline LambertianMaterial::LambertianMaterial(const Utility::Color& color) : 
	m_Color(color)
{
}

} // namespace Entity

#endif // ENTITY__LAMBERTIAN_MATERIAL
