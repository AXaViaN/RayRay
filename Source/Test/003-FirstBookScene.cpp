#include <Test/RayRayTest.h>
#include <Test/000-BookScenes.h>

namespace Test {

class FirstBookScene : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		return BookScenes::CreateFirstBookScene(-18, 11, -18, 11);
	}

	Entity::Camera SetupCamera(float aspectRatio)
	{
		auto position		=	Tool::Vector3f{9.0f, 2.0f, 5.0f};
		auto lookat			=	Tool::Vector3f{0.0f, 0.0f, 0.0f};
		auto up				=	Tool::Vector3f{0.0f, 1.0f, 0.0f};
		auto fov			=	30.0f;
		auto aperture		=	0.1f;
		auto focalOffset	=	0.0f;
		auto exposureTime	=	0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(FirstBookScene, 003);

} // namespace Test
