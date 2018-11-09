#include <Utility/Texture.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace Utility {

Texture::Texture(const Tool::Vector2u& size) : 
	m_Size(size),
	m_Data(m_Size.X * m_Size.Y, Tool::Color())
{
}

void Texture::Save(const std::string& fileName)
{
	static int ColorChannel = 3;

	std::vector<unsigned char> writeData;
	writeData.reserve(m_Size.X * m_Size.Y * ColorChannel);
	for( auto& color : m_Data )
	{
		writeData.emplace_back(unsigned char(255.99f * color.R));
		writeData.emplace_back(unsigned char(255.99f * color.G));
		writeData.emplace_back(unsigned char(255.99f * color.B));
	}

	stbi_write_png((fileName+".png").c_str(), m_Size.X, m_Size.Y, ColorChannel, writeData.data(), 0);
}

void Texture::SetPixel(const Tool::Vector2u& position, const Tool::Color& color)
{
	size_t inverseY = (m_Size.Y-1) - position.Y;
	m_Data[position.X + inverseY*m_Size.X] = color;
}
Tool::Color Texture::GetPixel(const Tool::Vector2u& position) const
{
	size_t inverseY = (m_Size.Y-1) - position.Y;
	return m_Data[position.X + inverseY*m_Size.X];
}

} // namespace Utility
