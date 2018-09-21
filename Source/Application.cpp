#include <Entity/Scene.h>
#include <Entity/Camera.h>
#include <Entity/Renderer.h>
#include <Entity/Sphere.h>
#include <Entity/LambertianMaterial.h>
#include <Tool/Texture.h>
#include <Utility/Color.h>
#include <Utility/Vector2.h>
#include <string>

static const std::string OutputFileName = "output";
static constexpr Utility::Vector2u OutputSize = {200, 100};
static constexpr size_t AASampleCount = 128;

int main()
{
	// Setup camera
	Entity::Camera camera({0.0f, 0.0f, 0.0f}, OutputSize.X/(float)OutputSize.Y);

	// Setup scene
	Entity::Scene scene;
	{
		Utility::Vector3f position;
		float radius;
		Entity::LambertianMaterial lambertianMaterial({});

		position = {0, -100.5f, -1};
		radius = 100.0f;
		lambertianMaterial = Entity::LambertianMaterial(Utility::Color{0.05f, 1.00f, 0.05f});
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Entity::LambertianMaterial>(lambertianMaterial)));

		position = {0, 0, -1};
		radius = 0.5f;
		lambertianMaterial = Entity::LambertianMaterial(Utility::Color{1.00f, 0.05f, 0.05f});
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Entity::LambertianMaterial>(lambertianMaterial)));
	}

	// Render
	Entity::Renderer renderer(OutputSize, AASampleCount);
	Tool::Texture renderTexture = renderer.RenderScene(scene, camera);

	renderTexture.Save(OutputFileName);

	return 0;
}
