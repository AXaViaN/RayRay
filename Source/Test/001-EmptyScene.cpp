#include <Test/RayRayTest.h>

namespace Test {

class EmptyScene : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		// Start/End time is needed for motion blur
		auto sceneStartTime	= 0.0f;
		auto sceneEndTime = 0.0f;
		auto scene = Entity::Scene(sceneStartTime, sceneEndTime);

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

REGISTER_RAYRAYTEST(EmptyScene, 1);

} // namespace Test
