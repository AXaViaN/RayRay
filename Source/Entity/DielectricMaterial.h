#ifndef ENTITY__DIELECTRIC_MATERIAL
#define ENTITY__DIELECTRIC_MATERIAL

#include <Entity/Material.h>

namespace Entity {

class DielectricMaterial : public Entity::Material
{
public:
	inline DielectricMaterial(float refractiveIndex);

	virtual Utility::ScatterResult ScatterCheck(const Tool::Ray& ray, const Utility::HitResult& hitResult) const override;

private:
	float m_RefractiveIndex = 0.0f;

};

inline DielectricMaterial::DielectricMaterial(float refractiveIndex) : 
	m_RefractiveIndex(refractiveIndex)
{
}

} // namespace Entity

#endif // ENTITY__DIELECTRIC_MATERIAL
