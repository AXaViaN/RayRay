#include <Entity/Scene.h>
#include <Entity/Camera.h>
#include <Entity/Sphere.h>
#include <Tool/Ray.h>
#include <Tool/Texture.h>
#include <Utility/Color.h>
#include <Utility/Vector2.h>
#include <Utility/Vector3.h>
#include <string>

static const std::string OutputFileName = "output";
static constexpr Utility::Vector2u OutputSize = {200, 100};

static Utility::Color GetBackgroundColor(const Tool::Ray& ray)
{
	auto direction = ray.GetDirection().Normalized();
	float t = 0.5f * (direction.Y + 1.0f);

	auto colorVector = Utility::Vector3f(0.2f, 0.4f, 0.8f) * t +
					   Utility::Vector3f(1.0f, 1.0f, 1.0f) * (1.0f-t);

	return {colorVector.X, colorVector.Y, colorVector.Z};
}

static Utility::Color GetColor(const Entity::Scene& scene, const Tool::Ray& ray)
{
	auto hitResult = scene.HitCheck(ray, 0.0f, std::numeric_limits<float>::max());
	if(hitResult.IsHit)
	{
		// Render normals for testing
		Utility::Vector3f normal = hitResult.Normal;

		// [-1,+1] -> [0,1]
		normal += {1, 1, 1};
		normal /= 2;

		return {normal.X, normal.Y, normal.Z};
	}

	return GetBackgroundColor(ray);
}

int main()
{
	// Setup texture output
	Tool::Texture output(OutputFileName, OutputSize);
	
	// Setup camera
	Entity::Camera camera({0.0f, 0.0f, 0.0f}, OutputSize.X/(float)OutputSize.Y);

	// Setup scene
	Entity::Scene scene;
	scene.AddSceneObject(Entity::Sphere(Utility::Color{1, 0, 0}, {0, 0, -1}, 0.5f));
	scene.AddSceneObject(Entity::Sphere(Utility::Color{0, 1, 0}, {0, -100.5f, -1}, 100.0f));

	// Traverse from lower-left
	Utility::Vector2u position;
	for( position.Y=0 ; position.Y<OutputSize.Y ; ++position.Y )
	{
		for( position.X=0 ; position.X<OutputSize.X ; ++position.X )
		{
			Utility::Vector2f uv = {
				float(position.X) / float(OutputSize.X),
				float(position.Y) / float(OutputSize.Y)
			};

			Tool::Ray ray = camera.GetRay(uv);
			Utility::Color color = GetColor(scene, ray);

			output.SetPixel(position, color);
		}
	}

	return 0;
}
