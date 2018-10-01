#ifndef GFX__RENDER_PLANE
#define GFX__RENDER_PLANE

#include <Tool/Vector2.h>
#include <Tool/Vector3.h>

namespace Gfx {

class RenderPlane
{
public:
	RenderPlane(const Tool::Vector3f& forward, const Tool::Vector3f& up, const Tool::Vector3f& right, const Tool::Vector3f& frustumSize);

	Tool::Vector3f GetPoint(const Tool::Vector2f& uv) const;

public:
	const Tool::Vector3f Up;
	const Tool::Vector3f Right;
	const Tool::Vector3f Forward;

private:
	Tool::Vector3f m_Horizontal;
	Tool::Vector3f m_Vertical;
	Tool::Vector3f m_LowerLeftCorner;

};

} // namespace Gfx

#endif // GFX__RENDER_PLANE
