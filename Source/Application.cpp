#include <Entity/Scene.h>
#include <Entity/Camera.h>
#include <Entity/Renderer.h>
#include <Entity/Sphere.h>
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
	scene.AddSceneObject(Entity::Sphere(Utility::Color{1, 0, 0}, 0.0f, {0, 0, -1}, 0.5f));
	scene.AddSceneObject(Entity::Sphere(Utility::Color{0, 1, 0}, 0.0f, {0, -100.5f, -1}, 100.0f));

	// Render
	Entity::Renderer renderer(OutputSize, AASampleCount);
	Tool::Texture renderTexture = renderer.RenderScene(scene, camera);

	renderTexture.Save(OutputFileName);

	return 0;
}
