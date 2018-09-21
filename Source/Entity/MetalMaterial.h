#ifndef ENTITY__METAL_MATERIAL
#define ENTITY__METAL_MATERIAL

#include <Entity/Material.h>
#include <algorithm>

namespace Entity {

class MetalMaterial : public Entity::Material
{
public:
	inline MetalMaterial(const Utility::Color& color, float fuzziness);

	virtual Utility::ScatterResult ScatterCheck(const Tool::Ray& ray, const Utility::HitResult& hitResult) const override;

private:
	Utility::Color m_Color;
	float m_Fuzziness = 0.0f;

};

inline MetalMaterial::MetalMaterial(const Utility::Color& color, float fuzziness) : 
	m_Color(color),
	m_Fuzziness(fuzziness)
{
	m_Fuzziness = std::clamp(m_Fuzziness, 0.0f, 1.0f);
}

} // namespace Entity

#endif // ENTITY__METAL_MATERIAL
