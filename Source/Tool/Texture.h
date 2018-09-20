#ifndef TOOL__TEXTURE
#define TOOL__TEXTURE

#include <Utility/Color.h>
#include <Utility/Vector2.h>
#include <string>
#include <vector>

namespace Tool {

class Texture
{
public:
	Texture(const Utility::Vector2u& size);

	void Save(const std::string& fileName, float gamma=2.0f);

	void SetPixel(const Utility::Vector2u& position, const Utility::Color& color);
	Utility::Color GetPixel(const Utility::Vector2u& position) const;

private:
	Utility::Vector2u m_Size;
	std::vector<Utility::Color> m_Data;

};

} // namespace Tool

#endif // TOOL__TEXTURE
