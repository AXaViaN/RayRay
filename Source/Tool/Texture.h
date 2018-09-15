#ifndef TOOL__TEXTURE
#define TOOL__TEXTURE

#include <Tool/File.h>
#include <Utility/Color.h>
#include <Utility/Vector2.h>
#include <string>
#include <vector>

namespace Tool {

class Texture
{
public:
	Texture(const std::string& fileName, const Utility::Vector2<size_t>& size);
	~Texture();
	
	void SetPixel(const Utility::Vector2<size_t>& position, const Utility::Color& color);
	Utility::Color GetPixel(const Utility::Vector2<size_t>& position) const;

private:
	Tool::File m_File;
	Utility::Vector2<size_t> m_Size;
	std::vector<Utility::Color> m_Data;

};

} // namespace Tool

#endif // TOOL__TEXTURE
