#ifndef TOOL__RENDER_PLANE
#define TOOL__RENDER_PLANE

#include <Utility/Vector3.h>

namespace Tool {

class RenderPlane
{
public:
	RenderPlane(Utility::Vector3<float> origin, Utility::Vector3<float> size, float screenRatio);

	inline const Utility::Vector3<float>& GetOrigin() const;
	inline const Utility::Vector3<float>& GetLowerLeft() const;
	inline const Utility::Vector3<float>& GetHorizontal() const;
	inline const Utility::Vector3<float>& GetVertical() const;

private:
	Utility::Vector3<float> m_Origin;
	Utility::Vector3<float> m_LowerLeftCorner;
	Utility::Vector3<float> m_Horizontal;
	Utility::Vector3<float> m_Vertical;

};

inline const Utility::Vector3<float>& RenderPlane::GetOrigin() const
{
	return m_Origin;
}
inline const Utility::Vector3<float>& RenderPlane::GetLowerLeft() const
{
	return m_LowerLeftCorner;
}
inline const Utility::Vector3<float>& RenderPlane::GetHorizontal() const
{
	return m_Horizontal;
}
inline const Utility::Vector3<float>& RenderPlane::GetVertical() const
{
	return m_Vertical;
}

} // namespace Tool

#endif // TOOL__RENDER_PLANE
