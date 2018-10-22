#ifndef ASSET__IMAGE_TEXTURE
#define ASSET__IMAGE_TEXTURE

#include <Asset/Texture.h>
#include <string>
#include <vector>

namespace Asset {

class ImageTexture : public Asset::Texture
{
public:
	ImageTexture(const std::string& fileName);

	virtual Tool::Color GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const override;

private:
	std::vector<Tool::Color> m_Data;
	Tool::Vector2u m_Size;

};

} // namespace Asset

#endif // ASSET__IMAGE_TEXTURE
