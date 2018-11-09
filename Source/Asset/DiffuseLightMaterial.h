#ifndef ASSET__DIFFUSE_LIGHT_MATERIAL
#define ASSET__DIFFUSE_LIGHT_MATERIAL

#include <Asset/Material.h>
#include <Tool/Color.h>

namespace Asset {

class DiffuseLightMaterial : public Asset::Material
{
public:
	DiffuseLightMaterial(const Tool::Color& color);

	virtual Tool::ScatterResult ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const override;
	virtual Tool::Color EmitColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const override;

private:
	Tool::Color m_Color;

};

} // namespace Asset

#endif // ASSET__DIFFUSE_LIGHT_MATERIAL
