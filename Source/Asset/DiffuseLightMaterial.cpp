#include <Asset/DiffuseLightMaterial.h>
#include <Tool/HitResult.h>
#include <Tool/ScatterResult.h>

namespace Asset {

DiffuseLightMaterial::DiffuseLightMaterial(const Tool::Color& color) : 
	m_Color(color)
{
}

Tool::ScatterResult DiffuseLightMaterial::ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const
{
	// No scattering
	return {};
}
Tool::Color DiffuseLightMaterial::EmitColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const
{
	return m_Color;
}

} // namespace Asset
