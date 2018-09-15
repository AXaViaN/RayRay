#include <Tool/Texture.h>
#include <Utility/Color.h>
#include <Utility/Vector2.h>
#include <string>

static const std::string OutputFileName = "output.ppm";
static constexpr Utility::Vector2<size_t> OutputSize = {200, 100};

int main()
{
	Tool::Texture output(OutputFileName, OutputSize);
	
	Utility::Vector2<size_t> position;
	for( position.Y=0 ; position.Y<OutputSize.Y ; ++position.Y )
	{
		for( position.X=0 ; position.X<OutputSize.X ; ++position.X )
		{
			Utility::Color color;
			color.R = float(position.X) / float(OutputSize.X);
			color.G = float(position.Y) / float(OutputSize.Y);
			color.B = 0.2f;

			output.SetPixel(position, color);
		}
	}

	return 0;
}
