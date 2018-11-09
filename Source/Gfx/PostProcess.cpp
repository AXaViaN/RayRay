#include <Gfx/PostProcess.h>
#include <Tool/Math.h>

namespace Gfx {

Utility::Texture PostProcess::Process(const Utility::Texture& input, const std::function<Tool::Color(const Tool::Color& color, const Tool::Vector2u& coord)>& pixelShader)
{
	auto& textureSize = input.GetSize();
	auto output = Utility::Texture(textureSize);

	for( auto y=0u ; y<textureSize.Y ; ++y )
	{
		for( auto x=0u ; x<textureSize.X ; ++x )
		{
			auto coord = Tool::Vector2u{x, y};
			auto color = input.GetPixel(coord);

			color = pixelShader(color, coord);
			output.SetPixel(coord, color);
		}
	}

	return output;
}

Utility::Texture PostProcess::GetLuminance(const Utility::Texture& input)
{
	auto shader = [](const Tool::Color& color, const Tool::Vector2u& coord) -> Tool::Color
	{
		auto luminance = color.R*0.2126f + color.G*0.7152f + color.B*0.0722f;
		if(luminance > 1.0f)
		{
			return color;
		}
		else
		{
			return {};
		}
	};

	return Process(input, shader);
}
Utility::Texture PostProcess::GaussianBlur(const Utility::Texture& input, size_t size)
{
	if(size % 2 == 0)
	{
		++size;
	}

	// Generate gaussian weights (1, 2, 4, 2, 1)
	auto weightCount = size * size;
	auto weights = std::vector<float>();
	weights.reserve(weightCount);
	for( auto i=0u ; i<size ; ++i )
	{
		auto yWeight = 0ull;
		if(i < Tool::Math::Ceil(size/2))
		{
			yWeight = Tool::Math::Pow(2u, i);
		}
		else
		{
			yWeight = Tool::Math::Pow(2ull, (size-1)-i);
		}

		for( auto j=0u ; j<size ; ++j )
		{
			auto xWeight = 0ull;
			if(j < Tool::Math::Ceil(size/2))
			{
				xWeight = Tool::Math::Pow(2u, j);
			}
			else
			{
				xWeight = Tool::Math::Pow(2ull, (size-1)-j);
			}

			auto value = static_cast<float>(yWeight * xWeight);
			weights.emplace_back(value / weightCount);
		}
	}

	auto& textureSize = input.GetSize();
	auto shader = [&input, &size, &weights, &textureSize](const Tool::Color& color, const Tool::Vector2u& coord) -> Tool::Color
	{
		auto newColor = Tool::Color();
		for( auto i=0 ; i<weights.size() ; ++i )
		{
			auto xOffset = static_cast<int>((i % size) - (size/2));
			auto yOffset = static_cast<int>((i / size) - (size/2));
			auto sampleCoord = Tool::Vector2u{coord.X+xOffset, coord.Y+yOffset};
			if(sampleCoord.X < 0 || 
			   sampleCoord.Y < 0 || 
			   sampleCoord.X >= textureSize.X || 
			   sampleCoord.Y >= textureSize.Y)
			{
				continue;
			}

			auto currColor = input.GetPixel(sampleCoord);

			newColor.R += currColor.R * weights.at(i);
			newColor.G += currColor.G * weights.at(i);
			newColor.B += currColor.B * weights.at(i);
		}

		return newColor;
	};

	return Process(input, shader);
}
Utility::Texture PostProcess::Bloom(const Utility::Texture& input, const Utility::Texture& highlight)
{
	auto shader = [&highlight](const Tool::Color& color, const Tool::Vector2u& coord) -> Tool::Color
	{
		auto bloomColor = highlight.GetPixel(coord);
		return {color.R + bloomColor.R, 
				color.G + bloomColor.G, 
				color.B + bloomColor.B};
	};

	return Process(input, shader);
}
Utility::Texture PostProcess::HDRToneMap(const Utility::Texture& input, float exposure)
{
	auto shader = [&exposure](const Tool::Color& color, const Tool::Vector2u& coord) -> Tool::Color
	{
		return {1.0f - Tool::Math::Exp(-color.R * exposure), 
				1.0f - Tool::Math::Exp(-color.G * exposure), 
				1.0f - Tool::Math::Exp(-color.B * exposure)};
	};

	return Process(input, shader);
}
Utility::Texture PostProcess::GammaCorrection(const Utility::Texture& input, float gamma)
{
	auto shader = [&gamma](const Tool::Color& color, const Tool::Vector2u& coord) -> Tool::Color
	{
		return {std::powf(color.R, 1.0f/gamma), 
				std::powf(color.G, 1.0f/gamma), 
				std::powf(color.B, 1.0f/gamma)};
	};

	return Process(input, shader);
}

} // namespace Gfx
