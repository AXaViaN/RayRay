#ifndef UTILITY__TEXTURE
#define UTILITY__TEXTURE

#include <Tool/Color.h>
#include <Tool/Vector2.h>
#include <string>
#include <vector>

namespace Utility {

class Texture
{
public:
	Texture(const Tool::Vector2u& size);

	void Save(const std::string& fileName, float gamma=2.0f);

	void SetPixel(const Tool::Vector2u& position, const Tool::Color& color);
	Tool::Color GetPixel(const Tool::Vector2u& position) const;

private:
	Tool::Vector2u m_Size;
	std::vector<Tool::Color> m_Data;

};

} // namespace Utility

#endif // UTILITY__TEXTURE
