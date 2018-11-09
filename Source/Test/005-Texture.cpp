#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Asset/CheckerTexture.h>
#include <Asset/ImageTexture.h>
#include <Asset/NoiseTexture.h>
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

		auto materials = std::vector<std::shared_ptr<Asset::Material>>();

		// Checker texture
		{
			auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 1.0f, 1.0f});

			auto firstColor = Tool::Color{0.1f, 0.25f, 0.5f};
			auto secondColor = Tool::Color{0.35f, 0.45f, 0.65f};
			auto cellSize = 0.5f;

			auto texture = std::make_shared<Asset::CheckerTexture>(firstColor, secondColor, cellSize);
			material->SetAlbedoTexture(texture);

			materials.emplace_back(std::move(material));
		}

		// Image texture
		{
			auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 1.0f, 1.0f});

			auto texture = std::make_shared<Asset::ImageTexture>("Data/earthmap.jpg");
			material->SetAlbedoTexture(texture);

			materials.emplace_back(std::move(material));
		}

		// Camouflage texture
		{
			auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{0.05f, 0.85f, 1.0f});

			auto type = Asset::NoiseTexture::NoiseType::Camouflage;
			auto color = Tool::Color{0.0f, 0.0f, 0.0f};
			auto scale = 2.0f;

			auto texture = std::make_shared<Asset::NoiseTexture>(type, color, scale);
			material->SetAlbedoTexture(texture);

			materials.emplace_back(std::move(material));
		}

		// Marble texture
		{
			auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{1.0f, 1.0f, 1.0f});

			auto type = Asset::NoiseTexture::NoiseType::Marble;
			auto color = Tool::Color{0.05f, 0.05f, 0.1f};
			auto scale = 7.0f;

			auto texture = std::make_shared<Asset::NoiseTexture>(type, color, scale);
			material->SetAlbedoTexture(texture);

			materials.emplace_back(std::move(material));
		}

		// One sphere for all materials
		auto radius = 3.0f;
		auto offset = 1.0f;
		for( auto i=0u ; i<materials.size() ; ++i )
		{
			auto totalSize = (materials.size() * radius*2.0f) + ((materials.size()-1u) * offset);
			auto leftPosX = - totalSize/2.0f + radius;
			auto posX = leftPosX + (radius*2.0f + offset)*i;

			auto position = Tool::Vector3f{posX, 0.0f, 0.0f};
			scene.AddSceneObject<Entity::Sphere>(position, radius, materials.at(i));
		}

		return scene;
	}

	Entity::Camera SetupCamera(float aspectRatio) override
	{
		auto position		=	Tool::Vector3f{0.0f, 0.0f, 30.0f};
		auto lookat			=	Tool::Vector3f{0.0f, 0.0f, 0.0f};
		auto up				=	Tool::Vector3f{0.0f, 1.0f, 0.0f};
		auto fov			=	30.0f;
		auto aperture		=	0.0f;
		auto focalOffset	=	0.0f;
		auto exposureTime	=	0.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(Texture, 5);

} // namespace Test
