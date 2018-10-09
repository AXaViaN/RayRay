#ifndef ASSET__TEXTURE
#define ASSET__TEXTURE

#include <Tool/Color.h>
#include <Tool/Vector2.h>
#include <Tool/Vector3.h>

namespace Asset {

class Texture
{
public:
	virtual Tool::Color GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const = 0;

};

} // namespace Asset

#endif // ASSET__TEXTURE
