#include <Asset/CheckerTexture.h>
#include <Tool/Math.h>

namespace Asset {

CheckerTexture::CheckerTexture(const Tool::Color& first, const Tool::Color& second) : 
	m_First(first),
	m_Second(second)
{
}

Tool::Color CheckerTexture::GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const
{
	float sines = Tool::Math::Sin(Tool::Math::ToAngle(10.0f * position.X)) * 
				  Tool::Math::Sin(Tool::Math::ToAngle(10.0f * position.Y)) * 
				  Tool::Math::Sin(Tool::Math::ToAngle(10.0f * position.Z));

	if(sines > 0)
	{
		return m_First;
	}
	else
	{
		return m_Second;
	}
}

} // namespace Asset
