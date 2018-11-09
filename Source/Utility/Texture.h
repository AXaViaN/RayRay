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

	void Save(const std::string& fileName);

	void SetPixel(const Tool::Vector2u& position, const Tool::Color& color);
	Tool::Color GetPixel(const Tool::Vector2u& position) const;

	inline const Tool::Vector2u& GetSize() const;

private:
	Tool::Vector2u m_Size;
	std::vector<Tool::Color> m_Data;

};

/***** IMPLEMENTATION *****/

inline const Tool::Vector2u& Texture::GetSize() const
{
	return m_Size;
}

} // namespace Utility

#endif // UTILITY__TEXTURE
