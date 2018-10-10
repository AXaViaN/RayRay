#include <Asset/CheckerTexture.h>
#include <Tool/Math.h>

namespace Asset {

CheckerTexture::CheckerTexture(const Tool::Color& firstColor, const Tool::Color& secondColor, float cellSize) : 
	m_FirstColor(firstColor),
	m_SecondColor(secondColor),
	m_CellSize(cellSize / Tool::Math::Pi())
{
}

Tool::Color CheckerTexture::GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const
{
	float sines = Tool::Math::SinRadian(position.X / m_CellSize) * 
				  Tool::Math::SinRadian(position.Y / m_CellSize) * 
				  Tool::Math::SinRadian(position.Z / m_CellSize);

	if(sines > 0)
	{
		return m_FirstColor;
	}
	else
	{
		return m_SecondColor;
	}
}

} // namespace Asset
