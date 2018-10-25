#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Asset/CheckerTexture.h>
#include <Asset/ImageTexture.h>
#include <Entity/Sphere.h>

namespace Test {

class Texture : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		auto sceneStartTime	= 0.0f;
		auto sceneEndTime = 0.0f;
		auto scene = Entity::Scene(sceneStartTime, sceneEndTime);

		// Checker texture
		auto checkerMaterial = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 1.0f, 1.0f});
		{
			auto firstColor = Tool::Color{0.1f, 0.25f, 0.5f};
			auto secondColor = Tool::Color{0.35f, 0.45f, 0.65f};
			auto cellSize = 0.5f;

			auto texture = std::make_shared<Asset::CheckerTexture>(firstColor, secondColor, cellSize);
			checkerMaterial->SetAlbedoTexture(texture);
		}

		// Image texture
		auto earthMaterial = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 1.0f, 1.0f});
		{
			auto texture = std::make_shared<Asset::ImageTexture>("Data/earthmap.jpg");
			earthMaterial->SetAlbedoTexture(texture);
		}

		// Left sphere
		{
			auto position = Tool::Vector3f{-5.0f, 0.0f, 0.0f};
			auto radius = 3.0f;
			scene.AddSceneObject<Entity::Sphere>(position, radius, earthMaterial);
		}
		
		// Right sphere
		{
			auto position = Tool::Vector3f{5.0f, 0.0f, 0.0f};
			auto radius = 3.0f;
			scene.AddSceneObject<Entity::Sphere>(position, radius, checkerMaterial);
		}

		return scene;
	}

	Entity::Camera SetupCamera(float aspectRatio) override
	{
		auto position		=	Tool::Vector3f{0.0f, 0.0f, 20.0f};
		auto lookat			=	Tool::Vector3f{0.0f, 0.0f, 0.0f};
		auto up				=	Tool::Vector3f{0.0f, 1.0f, 0.0f};
		auto fov			=	30.0f;
		auto aperture		=	0.0f;
		auto focalOffset	=	0.0f;
		auto exposureTime	=	0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(Texture, 005);

} // namespace Test
