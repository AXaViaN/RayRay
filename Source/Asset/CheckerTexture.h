#ifndef ASSET__CHECKER_TEXTURE
#define ASSET__CHECKER_TEXTURE

#include <Asset/Texture.h>
#include <Tool/Color.h>

namespace Asset {

class CheckerTexture : public Texture
{
public:
	CheckerTexture(const Tool::Color& first, const Tool::Color& second);

	virtual Tool::Color GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const override;

private:
	Tool::Color m_First;
	Tool::Color m_Second;

};

} // namespace Asset

#endif // ASSET__CHECKER_TEXTURE
