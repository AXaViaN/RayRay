#ifndef ASSET__METAL_MATERIAL
#define ASSET__METAL_MATERIAL

#include <Asset/Material.h>
#include <Tool/Color.h>

namespace Asset {

class MetalMaterial : public Asset::Material
{
public:
	MetalMaterial(const Tool::Color& color, float fuzziness);

	virtual Tool::ScatterResult ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const override;

private:
	Tool::Color m_Color;
	float m_Fuzziness = 0.0f;

};

} // namespace Asset

#endif // ASSET__METAL_MATERIAL
