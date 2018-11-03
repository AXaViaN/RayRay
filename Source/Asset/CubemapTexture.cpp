#include <Asset/CubemapTexture.h>
#include <Gfx/Util.h>
#include <Tool/Math.h>

namespace Asset {

static Tool::Vector2f FixUV(const Tool::Vector2f& cubemapUV, const Tool::Vector2f& cubeStep);

CubemapTexture::CubemapTexture(const std::string& fileName) : 
	m_Image(fileName)
{
}

Tool::Color CubemapTexture::GetColor(const Tool::Vector2f& uv, const Tool::Vector3f& position) const
{
	auto const cubeStep = Tool::Vector2f{1.0f/8.0f, 1.0f/6.0f};
	auto cubemapUV = Gfx::Util::GetSphericalUV(position);

	// Mirror x (we are in the inside)
	cubemapUV.X = 1.0f - cubemapUV.X;

	// Move x=0 to cubemap_left and wrap
	cubemapUV.X += cubeStep.X*3.0f;
	if(cubemapUV.X > 1.0f)
	{
		cubemapUV.X -= 1.0f;
	}

	// Move y from [0, 1] to [0, 0.666]
	cubemapUV.Y *= cubeStep.Y*4.0f;
	// Move y from [0, 0.666] to [0.166, 0.833]
	cubemapUV.Y += cubeStep.Y*1.0f;

	// Fix uv for top and bottom
	cubemapUV = FixUV(cubemapUV, cubeStep);

	return m_Image.GetColor(cubemapUV, position);
}

static Tool::Vector2f FixUV(const Tool::Vector2f& cubemapUV, const Tool::Vector2f& cubeStep)
{
	// Don't modify on sides
	if(cubemapUV.Y >= cubeStep.Y*2.0f && 
	   cubemapUV.Y <= cubeStep.Y*4.0f)
	{
		return cubemapUV;
	}

	// Select a starting point and up-right basis vectors. And move the uv

	// Back=0, Left=1, Front=2, Right=3
	auto regionIdx = static_cast<int>(cubemapUV.X / (cubeStep.X*2.0f));

	auto start = Tool::Vector3f{};
	start.X = cubeStep.X * (2.0f + 2.0f*((0b1100>>regionIdx)&1)); // *4, *4, *2, *2
	start.Y = cubeStep.Y * (0.0f + 2.0f*((0b0110>>regionIdx)&1)); // *0, *2, *2, *0

	auto right = Tool::Vector3f{};
	right.X = Tool::Math::Sin(90.0f * regionIdx); // 0, 1, 0, -1
	right.Y = Tool::Math::Sin(90.0f * regionIdx + 90.0f); // 1, 0, -1, 0

	auto up = Tool::Vector3f{};
	up.X = right.Y; // 1, 0, -1, 0
	up.Y = -right.X; // 0, -1, 0, 1

	// Movements are in [0, 1]
	auto movement = Tool::Vector3f{};
	movement.X = (cubemapUV.X - cubeStep.X*2.0f*regionIdx) / (cubeStep.X*2.0f);
	movement.Y = (cubemapUV.Y - cubeStep.Y*1.0f) / (cubeStep.Y*1.0f);

	// Top-bottom specific
	if(cubemapUV.Y < 0.5f)
	{
		// Top
		movement.Y = 1.0f - movement.Y;
	}
	else
	{
		// Bottom
		start.Y = 1.0f - start.Y;
		right.Y *= -1.0f;
		up.Y *= -1.0f;
		movement.Y -= (cubeStep.Y*3.0f) / (cubeStep.Y*1.0f);
	}

	// Restrict X based on Y to make triangle
	movement.X = (movement.X * (1.0f-movement.Y)) + (movement.Y / 2.0f);

	// Scale movements
	{
		float rFactor = cubeStep.Y;
		float uFactor = cubeStep.X;
		if((regionIdx % 2) == 1)
		{
			std::swap(rFactor, uFactor);
		}

		movement.X *= rFactor * 2.0f; // Y*, X*, Y*, X*
		movement.Y *= uFactor * 1.0f; // Y*, X*, Y*, X*
	}

	auto result = start + right*movement.X + up*movement.Y;
	return Tool::Vector2f{result.X, result.Y};
}

} // namespace Asset
