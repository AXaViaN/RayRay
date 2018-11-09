#include <Test/RayRayTest.h>
#include <Asset/DiffuseLightMaterial.h>
#include <Asset/LambertianMaterial.h>
#include <Asset/MetalMaterial.h>
#include <Entity/Sphere.h>

namespace Test {

class Light : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		auto sceneStartTime	= 0.0f;
		auto sceneEndTime = 0.0f;
		auto scene = Entity::Scene(sceneStartTime, sceneEndTime);

		// Make the sky black
		scene.Material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{0.0f, 0.0f, 0.0f});

		// Diffuse light sphere
		{
			auto position = Tool::Vector3f{0.0f, 4.0f, 0.0f};
			auto radius = 1.5f;
			auto intensity = 5.0f;
			auto material = std::make_shared<Asset::DiffuseLightMaterial>(Tool::Color{intensity, intensity, intensity});

			scene.AddSceneObject<Entity::Sphere>(position, radius, material);
		}

		// Ground
		{
			auto position = Tool::Vector3f{0.0f, -5000.0f, 0.0f};
			auto radius = 5000.0f;
			auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{0.6f, 0.2f, 0.8f});

			scene.AddSceneObject<Entity::Sphere>(position, radius, material);
		}

		// Center sphere
		{
			auto position = Tool::Vector3f{0.0f, 1.0f, -2.0f};
			auto radius = 1.0f;
			auto fuzziness = 0.0f;
			auto material = std::make_shared<Asset::MetalMaterial>(Tool::Color{1.0f, 1.0f, 1.0f}, fuzziness);

			scene.AddSceneObject<Entity::Sphere>(position, radius, material);
		}

		// Left sphere
		{
			auto position = Tool::Vector3f{-3.0f, 1.0f, 0.0f};
			auto radius = 1.0f;
			auto fuzziness = 0.0f;
			auto material = std::make_shared<Asset::MetalMaterial>(Tool::Color{1.0f, 1.0f, 1.0f}, fuzziness);

			scene.AddSceneObject<Entity::Sphere>(position, radius, material);
		}

		// Right sphere
		{
			auto position = Tool::Vector3f{3.0f, 1.0f, 0.0f};
			auto radius = 1.0f;
			auto fuzziness = 0.0f;
			auto material = std::make_shared<Asset::MetalMaterial>(Tool::Color{1.0f, 1.0f, 1.0f}, fuzziness);

			scene.AddSceneObject<Entity::Sphere>(position, radius, material);
		}

		return scene;
	}

	Entity::Camera SetupCamera(float aspectRatio) override
	{
		auto position		=	Tool::Vector3f{0.0f, 3.5f, 20.0f};
		auto lookat			=	Tool::Vector3f{0.0f, 1.0f, 0.0f};
		auto up				=	Tool::Vector3f{0.0f, 1.0f, 0.0f};
		auto fov			=	30.0f;
		auto aperture		=	0.0f;
		auto focalOffset	=	0.0f;
		auto exposureTime	=	0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(Light, 8);

} // namespace Test
