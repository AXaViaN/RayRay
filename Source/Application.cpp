#include <Tool/Texture.h>
#include <Utility/Color.h>
#include <Utility/Vector2.h>
#include <Utility/Vector3.h>
#include <Utility/Ray.h>
#include <string>

static const std::string OutputFileName = "output.ppm";
static constexpr Utility::Vector2<size_t> OutputSize = {200, 100};

static Utility::Color GetBackgroundColor(const Utility::Ray& ray)
{
	auto direction = ray.GetDirection().Normalized();
	float t = 0.5f * (direction.Y + 1.0f);

	auto colorVector = Utility::Vector3<float>(0.2f, 0.4f, 0.8f) * t +
					   Utility::Vector3<float>(1.0f, 1.0f, 1.0f) * (1.0f-t);

	return {colorVector.X, colorVector.Y, colorVector.Z};
}

int main()
{
	Tool::Texture output(OutputFileName, OutputSize);
	
	// Setup render plane
	Utility::Vector3<float> lowerLeftCorner = {-2.0f, -1.0f, -1.0f};
	Utility::Vector3<float> horizontal = {4.0f, 0.0f, 0.0f};
	Utility::Vector3<float> vertical = {0.0f, 2.0f, 0.0f};
	Utility::Vector3<float> origin = {0.0f, 0.0f, 0.0f};

	// Traverse from lower-left
	Utility::Vector2<size_t> position;
	for( position.Y=0 ; position.Y<OutputSize.Y ; ++position.Y )
	{
		for( position.X=0 ; position.X<OutputSize.X ; ++position.X )
		{
			Utility::Vector2<float> uv = {
				float(position.X) / float(OutputSize.X),
				float(position.Y) / float(OutputSize.Y)
			};

			Utility::Ray ray(origin, lowerLeftCorner + horizontal*uv.X + vertical*uv.Y);
			Utility::Color color = GetBackgroundColor(ray);

			output.SetPixel(position, color);
		}
	}

	return 0;
}
