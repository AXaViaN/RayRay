#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Asset/CubemapTexture.h>

namespace Test {

class Skybox : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		auto sceneStartTime	= 0.0f;
		auto sceneEndTime = 0.0f;
		auto scene = Entity::Scene(sceneStartTime, sceneEndTime);

		// Create cubemap
		auto texture = std::make_shared<Asset::CubemapTexture>("Data/skybox_000.jpg");

		// Set scene material for skybox
		scene.Material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 1.0f, 1.0f});
		scene.Material->SetAlbedoTexture(texture);

		return scene;
	}

	Entity::Camera SetupCamera(float aspectRatio) override
	{
		auto position		=	Tool::Vector3f{0.0f, 0.0f, 0.0f};
		auto lookat			=	Tool::Vector3f{-1.0f, 1.0f, 0.0f};
		auto up				=	Tool::Vector3f{0.0f, 1.0f, 0.0f};
		auto fov			=	90.0f;
		auto aperture		=	0.0f;
		auto focalOffset	=	0.0f;
		auto exposureTime	=	0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(Skybox, 7);

} // namespace Test
