#include <Test/RayRayTest.h>
#include <Asset/LambertianMaterial.h>
#include <Asset/MetalMaterial.h>
#include <Asset/DielectricMaterial.h>
#include <Asset/CheckerTexture.h>
#include <Entity/Sphere.h>
#include <Tool/Random.h>

namespace Test {

class MotionBlur : public Test::RayRayTest
{
private:
	Entity::Scene SetupScene() override
	{
		// Moving version of first book (small lambertian balls are moving)
		Entity::Scene scene;
		Tool::Random random;

		Tool::Vector3f position;
		float radius;
		Asset::LambertianMaterial lambertianMaterial({});
		Asset::MetalMaterial metalMaterial({}, 0);
		Asset::DielectricMaterial dielectricMaterial(0);
		auto checkerTexture = std::make_shared<Asset::CheckerTexture>(Tool::Color{0.1f, 0.25f, 0.5f}, 
																	  Tool::Color{0.35f, 0.45f, 0.65f},
																	  0.3f);

		// Ground
		position = {0.0f, -1000.0f, 0.0f};
		radius = 1000.0f;
		metalMaterial = Asset::MetalMaterial(Tool::Color{0.75f, 0.75f, 0.75f}, 0.25f);
		metalMaterial.SetAlbedoTexture(checkerTexture);
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Asset::MetalMaterial>(metalMaterial)));

		// Center
		position = {0.0f, 1.0f, 0.0f};
		radius = 1.0f;
		dielectricMaterial = Asset::DielectricMaterial(1.5f);
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Asset::DielectricMaterial>(dielectricMaterial)));

		// Right metal
		position = {3.0f, 1.0f, 0.0f};
		radius = 1.0f;
		metalMaterial = Asset::MetalMaterial(Tool::Color{0.7f, 0.6f, 0.5f}, 0.0f);
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Asset::MetalMaterial>(metalMaterial)));

		// Left glass
		position = {-3.0f, 1.0f, 0.0f};
		radius = 1.0f;
		dielectricMaterial = Asset::DielectricMaterial(1.5f);
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Asset::DielectricMaterial>(dielectricMaterial)));
		position = {-3.0f, 1.0f, 0.0f};
		radius = -0.95f;
		dielectricMaterial = Asset::DielectricMaterial(1.5f);
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Asset::DielectricMaterial>(dielectricMaterial)));

		// Left lambertian
		position = {-6.0f, 1.0f, 0.0f};
		radius = 1.0f;
		lambertianMaterial = Asset::LambertianMaterial(Tool::Color{0.2f, 0.4f, 0.8f});
		scene.AddSceneObject(Entity::Sphere(position, radius, 
											std::make_unique<Asset::LambertianMaterial>(lambertianMaterial)));

		// Random balls
		radius = 0.2f;
		for( int x=-5 ; x<5 ; ++x )
		{
			for( int z=-5 ; z<3 ; ++z )
			{
				position = {x+0.9f*random.GetFloat(), radius, z+0.9f*random.GetFloat()};
				if((position-Tool::Vector3f(4.0f, radius, 0.0f)).Length() > 0.9f)
				{
					float chooseMaterial = random.GetFloat();
					if(chooseMaterial < 0.6f)
					{
						Tool::Color color{random.GetFloat()*random.GetFloat(), 
							random.GetFloat()*random.GetFloat(), 
							random.GetFloat()*random.GetFloat()};
						lambertianMaterial = Asset::LambertianMaterial(color);
						auto sphere = Entity::Sphere(position, radius, 
													 std::make_unique<Asset::LambertianMaterial>(lambertianMaterial));

						auto moveDirection = Tool::Vector3f{0.0f, 0.5f, 0.0f} * random.GetFloat();
						sphere.Move(position + moveDirection, 0.0f, 1.0f);

						scene.AddSceneObject(std::move(sphere));
					}
					else if(chooseMaterial < 0.85f)
					{
						Tool::Color color{random.GetFloat()*random.GetFloat(), 
							random.GetFloat()*random.GetFloat(), 
							random.GetFloat()*random.GetFloat()};
						metalMaterial = Asset::MetalMaterial(color, 0.5f*random.GetFloat());
						scene.AddSceneObject(Entity::Sphere(position, radius, 
															std::make_unique<Asset::MetalMaterial>(metalMaterial)));
					}
					else
					{
						dielectricMaterial = Asset::DielectricMaterial(1.5f);
						scene.AddSceneObject(Entity::Sphere(position, radius, 
															std::make_unique<Asset::DielectricMaterial>(dielectricMaterial)));
					}
				}
			}
		}

		return scene;
	}

	Entity::Camera SetupCamera(float aspectRatio) override
	{
		Tool::Vector3f position = {9.0f, 2.0f, 5.0f};
		Tool::Vector3f lookat = {0.0f, 0.0f, 0.0f};
		Tool::Vector3f up = {0.0f, 1.0f, 0.0f};
		float fov = 30.0f;
		float aperture = 0.001f;
		float focalOffset = 0.0f;
		float exposureTime = 1.0f;

		return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, exposureTime, aspectRatio);
	}
};

REGISTER_RAYRAYTEST(MotionBlur, 004);

} // namespace Test
