#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Entity/Sphere.h>

namespace Test {

class RedSphere : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		Entity::Scene scene;

		Tool::Vector3f position = {0.0f, 0.0f, -2.0f};
		float radius = 1.0f;
		Asset::LambertianMaterial material({1.0f, 0.0f, 0.0f});
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Asset::LambertianMaterial>(material)));

		return scene;
	}

	Entity::Camera SetupCamera(float aspectRatio) override
	{
		Tool::Vector3f position = {0.0f, 0.0f, 0.0f};
		Tool::Vector3f lookat = {0.0f, 0.0f, -2.0f};
		Tool::Vector3f up = {0.0f, 1.0f, 0.0f};
		float fov = 90.0f;
		float aperture = 0.0f;
		float focalOffset = 0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(RedSphere, 002);

} // namespace Test
