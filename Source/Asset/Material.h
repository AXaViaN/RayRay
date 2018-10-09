#ifndef ASSET__MATERIAL
#define ASSET__MATERIAL

#include <Asset/Texture.h>
#include <Tool/Color.h>
#include <memory>

namespace Tool {
	class Ray;
	class HitResult;
	class ScatterResult;
}

namespace Asset {

class Material
{
public:
	virtual Tool::ScatterResult ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const = 0;

	inline void SetAlbedoTexture(std::shared_ptr<Asset::Texture> albedo);
	inline Tool::Color GetAlbedoColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const;

private:
	std::shared_ptr<Asset::Texture> m_Albedo;

};

inline void Material::SetAlbedoTexture(std::shared_ptr<Asset::Texture> albedo)
{
	m_Albedo = albedo;
}
inline Tool::Color Material::GetAlbedoColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const
{
	Tool::Color color = {1.0f, 1.0f, 1.0f};
	if(m_Albedo != nullptr)
	{
		color = m_Albedo->GetColor(uv, position);
	}
	return color;
}

} // namespace Asset

#endif // ASSET__MATERIAL
