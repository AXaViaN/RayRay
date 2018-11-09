#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Entity/Sphere.h>

namespace Test {

class RedSphere : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		auto sceneStartTime	= 0.0f;
		auto sceneEndTime = 0.0f;
		auto scene = Entity::Scene(sceneStartTime, sceneEndTime);

		// Sphere attributes
		auto position = Tool::Vector3f{0.0f, 0.0f, 0.0f};
		auto radius = 1.0f;
		auto redMaterial = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 0.0f, 0.0f});

		// Construct at point
		scene.AddSceneObject<Entity::Sphere>(position, radius, redMaterial);
		
		// Copy object
		//auto sphere = Entity::Sphere(position, radius, redMaterial);
		//scene.AddSceneObject(sphere);
		
		return scene;
	}

	Entity::Camera SetupCamera(float aspectRatio) override
	{
		auto position		=	Tool::Vector3f{0.0f, 0.0f, 5.0f};
		auto lookat			=	Tool::Vector3f{0.0f, 0.0f, 0.0f};
		auto up				=	Tool::Vector3f{0.0f, 1.0f, 0.0f};
		auto fov			=	30.0f;
		auto aperture		=	0.0f;
		auto focalOffset	=	0.0f;
		auto exposureTime	=	0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(RedSphere, 2);

} // namespace Test
