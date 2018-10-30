#include <Asset/NoiseTexture.h>
#include <Tool/Math.h>

namespace Asset {

NoiseTexture::NoiseTexture(NoiseType noiseType, const Tool::Color& color, float scale) : 
	m_NoiseType(noiseType), 
	m_Color(color), 
	m_Scale(scale)
{
}

Tool::Color NoiseTexture::GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const
{
	auto totalNoise = 0.0f;
	switch(m_NoiseType)
	{
		case Asset::NoiseTexture::NoiseType::Camouflage:
		{
			auto noise = m_Perlin.Turbulence(position * m_Scale);

			totalNoise = noise;
			break;
		}
		case Asset::NoiseTexture::NoiseType::Marble:
		{
			auto noise = m_Perlin.Turbulence(position);

			totalNoise = (1.0f + Tool::Math::SinRadian(position.Z*m_Scale + noise*10.0f)) * 0.5f;
			break;
		}
	}

	return Tool::Color{
		totalNoise + (1.0f-totalNoise)*m_Color.R, 
		totalNoise + (1.0f-totalNoise)*m_Color.G, 
		totalNoise + (1.0f-totalNoise)*m_Color.B
	};
}

} // namespace Asset
