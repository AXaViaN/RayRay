#ifndef TEST__BOOK_SCENES
#define TEST__BOOK_SCENES

#include <Asset/LambertianMaterial.h>
#include <Asset/MetalMaterial.h>
#include <Asset/DielectricMaterial.h>
#include <Entity/Sphere.h>
#include <Entity/Scene.h>
#include <Tool/Random.h>

namespace Test {

class BookScenes
{
public:
	static inline Entity::Scene CreateFirstBookScene(int xStart, int xEnd, int zStart, int zEnd);

private:
	static inline Entity::Sphere GetRandomSphere(Tool::Vector3f position, Tool::Random& random);

};

/***** IMPLEMENTATION *****/

inline Entity::Scene BookScenes::CreateFirstBookScene(int xStart, int xEnd, int zStart, int zEnd)
{
	auto sceneStartTime = 0.0f;
	auto sceneEndTime = 0.0f;
	auto scene = Entity::Scene(sceneStartTime, sceneEndTime);
	auto random = Tool::Random();

	// Ground
	{
		auto position = Tool::Vector3f{0.0f, -1000.0f, 0.0f};
		auto radius = 1000.0f;
		auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{0.75f, 0.75f, 0.75f});
		scene.AddSceneObject<Entity::Sphere>(position, radius, material);
	}

	// Center dielectric
	{
		auto position = Tool::Vector3f{0.0f, 1.0f, 0.0f};
		auto radius = 1.0f;
		auto material = std::make_shared<Asset::DielectricMaterial>(2.5f);
		scene.AddSceneObject<Entity::Sphere>(position, radius, material);
	}

	// Right metal
	{
		auto position = Tool::Vector3f{3.0f, 1.0f, 0.0f};
		auto radius = 1.0f;
		auto fuzziness = 0.0f;
		auto material = std::make_shared<Asset::MetalMaterial>(Tool::Color{0.7f, 0.6f, 0.5f}, fuzziness);
		scene.AddSceneObject<Entity::Sphere>(position, radius, material);
	}

	// Left glass
	{
		auto position = Tool::Vector3f{-3.0f, 1.0f, 0.0f};
		auto radius = 1.0f;
		auto material = std::make_shared<Asset::DielectricMaterial>(1.5f);
		scene.AddSceneObject<Entity::Sphere>(position, radius, material);

		radius = -0.95f;
		scene.AddSceneObject<Entity::Sphere>(position, radius, material);
	}

	// Left lambertian
	{
		auto position = Tool::Vector3f{-6.0f, 1.0f, 0.0f};
		auto radius = 1.0f;
		auto material = std::make_shared<Asset::LambertianMaterial>(Tool::Color{0.2f, 0.4f, 0.8f});
		scene.AddSceneObject<Entity::Sphere>(position, radius, material);
	}

	// Random balls
	for( int x=xStart ; x<xEnd ; ++x )
	{
		for( int z=zStart ; z<zEnd ; ++z )
		{
			auto constexpr radius = 0.2f;
			auto position = Tool::Vector3f{(float)x, radius, (float)z};

			auto sphere = GetRandomSphere(position, random);
			scene.AddSceneObject(sphere);
		}
	}

	return scene;
}

inline Entity::Sphere BookScenes::GetRandomSphere(Tool::Vector3f position, Tool::Random& random)
{
	auto radius = position.Y;
	position.X += 0.9f * random.GetFloat();
	position.Z += 0.9f * random.GetFloat();

	auto material = std::shared_ptr<Asset::Material>();
	auto chooseMaterial = random.GetFloat();
	if(chooseMaterial < 0.6f)
	{
		auto color = Tool::Color{
			random.GetFloat()*random.GetFloat(), 
			random.GetFloat()*random.GetFloat(), 
			random.GetFloat()*random.GetFloat()
		};

		material = std::make_shared<Asset::LambertianMaterial>(color);
	}
	else if(chooseMaterial < 0.85f)
	{
		auto color = Tool::Color{
			random.GetFloat()*random.GetFloat(), 
			random.GetFloat()*random.GetFloat(), 
			random.GetFloat()*random.GetFloat()
		};
		auto fuzziness = 0.5f * random.GetFloat();

		material = std::make_shared<Asset::MetalMaterial>(color, fuzziness);
	}
	else
	{
		material = std::make_shared<Asset::DielectricMaterial>(1.5f);
	}

	return Entity::Sphere(position, radius, material);
}

} // namespace Test

#endif // TEST__BOOK_SCENES
