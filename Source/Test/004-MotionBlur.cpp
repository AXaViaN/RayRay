#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Entity/Sphere.h>

namespace Test {

class MotionBlur : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		// Mind the values of scene times, moveData times and camera exposureTime

		auto sceneStartTime	= 0.0f;
		auto sceneEndTime = 10.0f;
		auto scene = Entity::Scene(sceneStartTime, sceneEndTime);

		// Sphere
		auto position = Tool::Vector3f{0.0f, 0.0f, 0.0f};
		auto radius = 1.0f;
		auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{0.01f, 0.1f, 0.9f});
		auto sphere = Entity::Sphere(position, radius, material);

		// Movement
		{
			auto movement = Tool::Vector3f{1.0f, 0.0f, 0.0f};

			auto moveData = Entity::Sphere::MoveData();
			moveData.Target = position + movement;
			moveData.StartTime = 0.0f;
			moveData.EndTime = 2.0f;
			sphere.Move(moveData);
		}

		scene.AddSceneObject(sphere);

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
		auto exposureTime	=	1.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(MotionBlur, 004);

} // namespace Test
