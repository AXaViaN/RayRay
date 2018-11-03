#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Asset/MetalMaterial.h>
#include <Asset/CheckerTexture.h>
#include <Asset/CubemapTexture.h>
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

		// Add checker texture for the ground
		{
			auto position = Tool::Vector3f{0.0f, -5000.0f, 0.0f};
			auto radius = 5000.01f; // 5000 for checker seams, .01 for putting it up
			auto fuzziness = 0.75f;
			auto material = std::make_shared<Asset::MetalMaterial>(Tool::Color{1.0f, 1.0f, 1.0f}, fuzziness);
			{
				auto firstColor = Tool::Color{0.1f, 0.25f, 0.5f};
				auto secondColor = Tool::Color{0.35f, 0.45f, 0.65f};
				auto cellSize = 0.5f;

				auto texture = std::make_shared<Asset::CheckerTexture>(firstColor, secondColor, cellSize);
				material->SetAlbedoTexture(texture);
			}

			firstBookScene.AddSceneObject<Entity::Sphere>(position, radius, material);
		}

		// Add skybox
		{
			auto texture = std::make_shared<Asset::CubemapTexture>("Data/skybox_000.jpg");

			firstBookScene.Material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 1.0f, 1.0f});
			firstBookScene.Material->SetAlbedoTexture(texture);
		}

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
