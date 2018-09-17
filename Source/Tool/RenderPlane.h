#ifndef TOOL__RENDER_PLANE
#define TOOL__RENDER_PLANE

#include <Utility/Vector3.h>

namespace Tool {

class RenderPlane
{
public:
	RenderPlane(const Utility::Vector3f& origin, const Utility::Vector3f& size, float screenRatio);

	inline const Utility::Vector3f& GetOrigin() const;
	inline const Utility::Vector3f& GetLowerLeft() const;
	inline const Utility::Vector3f& GetHorizontal() const;
	inline const Utility::Vector3f& GetVertical() const;

private:
	Utility::Vector3f m_Origin;
	Utility::Vector3f m_LowerLeftCorner;
	Utility::Vector3f m_Horizontal;
	Utility::Vector3f m_Vertical;

};

inline const Utility::Vector3f& RenderPlane::GetOrigin() const
{
	return m_Origin;
}
inline const Utility::Vector3f& RenderPlane::GetLowerLeft() const
{
	return m_LowerLeftCorner;
}
inline const Utility::Vector3f& RenderPlane::GetHorizontal() const
{
	return m_Horizontal;
}
inline const Utility::Vector3f& RenderPlane::GetVertical() const
{
	return m_Vertical;
}

} // namespace Tool

#endif // TOOL__RENDER_PLANE
