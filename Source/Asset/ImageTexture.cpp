#include <Asset/ImageTexture.h>
#include <Tool/Math.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <algorithm>

namespace Asset {

static void LogWarning(const std::string& message)
{
	std::printf("Warning: %s\n", message.c_str());
	std::getchar();
}

ImageTexture::ImageTexture(const std::string& fileName)
{
	static int ColorChannel = 3;

	float* rawImage;
	{
		int x;
		int y;
		int channel;
		rawImage = stbi_loadf(fileName.c_str(), &x, &y, &channel, ColorChannel);
		if(rawImage == nullptr)
		{
			LogWarning(std::string("Can not open file \"") + fileName + "\": " + stbi_failure_reason());
			return;
		}

		m_Size.X = x;
		m_Size.Y = y;
	}

	m_Data.reserve(m_Size.X * m_Size.Y);
	for( size_t y=0 ; y<m_Size.Y ; ++y )
	{
		for( size_t x=0 ; x<m_Size.X ; ++x )
		{
			size_t idx = (y*m_Size.X + x) * ColorChannel;

			m_Data.emplace_back(Tool::Color{
				rawImage[idx + 0],
				rawImage[idx + 1],
				rawImage[idx + 2]
			});
		}
	}

	stbi_image_free(rawImage);
}

Tool::Color ImageTexture::GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const
{
	Tool::Vector2u coord = {
		static_cast<Tool::Vector2u::Type>(m_Size.X * uv.X),
		static_cast<Tool::Vector2u::Type>(m_Size.Y * uv.Y)
	};
	coord.X = std::clamp(coord.X, 0u, m_Size.X-1);
	coord.Y = std::clamp(coord.Y, 0u, m_Size.Y-1);

	size_t idx = (coord.Y*m_Size.X + coord.X);
	if(idx >= m_Data.size())
	{
		return {};
	}

	return m_Data[idx];
}

} // namespace Asset
