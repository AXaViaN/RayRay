#ifndef ASSET__CUBEMAP_TEXTURE
#define ASSET__CUBEMAP_TEXTURE

#include <Asset/Texture.h>
#include <Asset/ImageTexture.h>
#include <string>
#include <vector>

namespace Asset {

class CubemapTexture : public Asset::Texture
{
public:
	CubemapTexture(const std::string& fileName);

	virtual Tool::Color GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const override;

private:
	Asset::ImageTexture m_Image;

};

} // namespace Asset

#endif // ASSET__CUBEMAP_TEXTURE
