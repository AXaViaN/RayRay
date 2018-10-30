#ifndef ASSET__NOISE_TEXTURE
#define ASSET__NOISE_TEXTURE

#include <Asset/Texture.h>
#include <Tool/Perlin.h>

namespace Asset {

class NoiseTexture : public Asset::Texture
{
public:
	enum class NoiseType;

public:
	NoiseTexture(NoiseType noiseType, const Tool::Color& color, float scale);

	virtual Tool::Color GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const override;

private:
	NoiseType m_NoiseType;
	Tool::Color m_Color;

	Tool::Perlin m_Perlin;
	float m_Scale;

};

enum class NoiseTexture::NoiseType
{
	Camouflage, 
	Marble
};

} // namespace Asset

#endif // ASSET__NOISE_TEXTURE
