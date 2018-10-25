#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Asset/MetalMaterial.h>
#include <Asset/ImageTexture.h>
#include <Entity/Sphere.h>
#include <Test/000-BookScenes.h>

namespace Test {

class EarthScene : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene()
	{
		auto firstBookScene = BookScenes::CreateFirstBookScene(-45, 9, -9, 40);

		// Earth
		{
			auto position = Tool::Vector3f{2.5f, 1.75f, 6.0f};
			auto radius = 1.75f;
			auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 1.0f, 1.0f});
			auto texture = std::make_shared<Asset::ImageTexture>("Data/earthmap.jpg");

			material->SetAlbedoTexture(texture);
			firstBookScene.AddSceneObject<Entity::Sphere>(position, radius, material);
		}

		// Metal
		{
			auto position = Tool::Vector3f{-2.5f, 1.75f, 5.0f};
			auto radius = 1.75f;
			auto fuzziness = 0.5f;
			auto material = std::make_shared<Asset::MetalMaterial>(Tool::Color{1.0f, 1.0f, 1.0f}, fuzziness);
			auto texture = std::make_shared<Asset::ImageTexture>("Data/metal.jpg");

			material->SetAlbedoTexture(texture);
			firstBookScene.AddSceneObject<Entity::Sphere>(position, radius, material);
		}
		
		// Stone
		{
			auto position = Tool::Vector3f{-8.0f, 1.75f, 3.5f};
			auto radius = 1.75f;
			auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 1.0f, 1.0f});
			auto texture = std::make_shared<Asset::ImageTexture>("Data/stone.jpg");

			material->SetAlbedoTexture(texture);
			firstBookScene.AddSceneObject<Entity::Sphere>(position, radius, material);
		}

		return firstBookScene;
	}

	Entity::Camera SetupCamera(float aspectRatio)
	{
		auto position		=	Tool::Vector3f{13.0f, 7.0f, -5.0f};
		auto lookat			=	Tool::Vector3f{0.0f, 1.0f, 2.0f};
		auto up				=	Tool::Vector3f{0.0f, 1.0f, 0.0f};
		auto fov			=	30.0f;
		auto aperture		=	0.15f;
		auto focalOffset	=	0.0f;
		auto exposureTime	=	0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(EarthScene, 006);

} // namespace Test
