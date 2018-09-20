#include <Tool/Texture.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace Tool {

Texture::Texture(const Utility::Vector2u& size) : 
	m_Size(size),
	m_Data(m_Size.X * m_Size.Y, Utility::Color())
{
}

void Texture::Save(const std::string& fileName, float gamma)
{
	static size_t ColorChannel = 3;

	std::vector<unsigned char> writeData;
	writeData.reserve(m_Size.X * m_Size.Y * ColorChannel);
	for( auto& color : m_Data )
	{
		// Gamma correction
		color = {std::powf(color.R, 1.0f/gamma), 
				 std::powf(color.G, 1.0f/gamma),
				 std::powf(color.B, 1.0f/gamma)};

		writeData.emplace_back(unsigned char(255.99f * color.R));
		writeData.emplace_back(unsigned char(255.99f * color.G));
		writeData.emplace_back(unsigned char(255.99f * color.B));
	}

	stbi_write_png((fileName+".png").c_str(), m_Size.X, m_Size.Y, ColorChannel, writeData.data(), 0);
}

void Texture::SetPixel(const Utility::Vector2u& position, const Utility::Color& color)
{
	size_t inverseY = (m_Size.Y-1) - position.Y;
	m_Data[position.X + inverseY*m_Size.X] = color;
}
Utility::Color Texture::GetPixel(const Utility::Vector2u& position) const
{
	size_t inverseY = (m_Size.Y-1) - position.Y;
	return m_Data[position.X + inverseY*m_Size.X];
}

} // namespace Tool
