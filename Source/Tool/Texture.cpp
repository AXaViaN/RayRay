#include <Tool/Texture.h>

namespace Tool {

static const std::string ColorFormat = "P3";
static constexpr int MaxColor = 255;

Texture::Texture(const std::string& fileName, const Utility::Vector2<size_t>& size) : 
	m_File(fileName, Tool::File::Type::Text),
	m_Size(size),
	m_Data(m_Size.X * m_Size.Y, Utility::Color())
{
	m_File.DeleteContents();
	m_File.WriteLine(ColorFormat);
	m_File.WriteLine(std::to_string(m_Size.X) + " " + std::to_string(m_Size.Y));
	m_File.WriteLine(std::to_string(MaxColor));
}
Texture::~Texture()
{
	for( auto& color : m_Data )
	{
		int r = int(255.99f * color.R);
		int g = int(255.99f * color.G);
		int b = int(255.99f * color.B);

		m_File.WriteLine(std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b));
	}
}

void Texture::SetPixel(const Utility::Vector2<size_t>& position, const Utility::Color& color)
{
	m_Data[position.X + position.Y*m_Size.X] = color;
}
Utility::Color Texture::GetPixel(const Utility::Vector2<size_t>& position) const
{
	return m_Data[position.X + position.Y*m_Size.X];
}

} // namespace Tool
