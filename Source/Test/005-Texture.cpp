#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Asset/CheckerTexture.h>
#include <Entity/Sphere.h>

namespace Test {

class Texture : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		float sceneStartTime = 0.0f;
		float sceneEndTime = 0.0f;
		Entity::Scene scene(sceneStartTime, sceneEndTime);

		float checkerCellSize = 1.0f;
		auto checkerTexture = std::make_shared<Asset::CheckerTexture>(Tool::Color{0.1f, 0.25f, 0.5f}, 
																	  Tool::Color{0.35f, 0.45f, 0.65f}, 
																	  checkerCellSize);

		auto position = Tool::Vector3f{0.0f, -1000.0f, 0.0f};
		auto radius = 1000.0f;
		auto material = Asset::LambertianMaterial(Tool::Color{0.75f, 0.75f, 0.75f});
		material.SetAlbedoTexture(checkerTexture);
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Asset::LambertianMaterial>(material)));

		return scene;
	}

	Entity::Camera SetupCamera(float aspectRatio) override
	{
		Tool::Vector3f position = {0.0f, 1.0f, 0.0f};
		Tool::Vector3f lookat = {0.0f, 0.0f, -2.0f};
		Tool::Vector3f up = {0.0f, 1.0f, 0.0f};
		float fov = 90.0f;
		float aperture = 0.0f;
		float focalOffset = 0.0f;
		float exposureTime = 0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(Texture, 005);

} // namespace Test
