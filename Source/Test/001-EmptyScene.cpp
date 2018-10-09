#include <Test/RayRayTest.h>

namespace Test {

class EmptyScene : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		Entity::Scene scene;
		return scene;
	}

	Entity::Camera SetupCamera(float aspectRatio) override
	{
		Tool::Vector3f position = {0.0f, 0.0f, 0.0f};
		Tool::Vector3f lookat = {0.0f, 0.0f, -1.0f};
		Tool::Vector3f up = {0.0f, 1.0f, 0.0f};
		float fov = 90.0f;
		float aperture = 0.0f;
		float focalOffset = 0.0f;
		float exposureTime = 0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(EmptyScene, 001);

} // namespace Test
