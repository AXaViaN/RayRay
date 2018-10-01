#include <Asset/LambertianMaterial.h>
#include <Asset/MetalMaterial.h>
#include <Asset/DielectricMaterial.h>
#include <Entity/Scene.h>
#include <Entity/Camera.h>
#include <Entity/Sphere.h>
#include <Gfx/Renderer.h>
#include <Tool/Color.h>
#include <Tool/Vector2.h>
#include <Tool/Vector3.h>
#include <Utility/Texture.h>
#include <Tool/Random.h>
#include <string>

static const std::string OutputFileName = "output";
static constexpr Tool::Vector2u OutputSize = {200, 100};
static constexpr size_t AASampleCount = 128;

static Entity::Scene CreateScene()
{
	Entity::Scene scene;
	Tool::Random random;

	Tool::Vector3f position;
	float radius;
	Asset::LambertianMaterial lambertianMaterial({});
	Asset::MetalMaterial metalMaterial({}, 0);
	Asset::DielectricMaterial dielectricMaterial(0);

	// Ground
	position = {0.0f, -1000.0f, 0.0f};
	radius = 1000.0f;
	lambertianMaterial = Asset::LambertianMaterial(Tool::Color{0.75f, 0.75f, 0.75f});
	scene.AddSceneObject(Entity::Sphere(position, radius, 
										std::make_unique<Asset::LambertianMaterial>(lambertianMaterial)));

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
#if 1
	radius = 0.2f;
	for( int x=-18 ; x<11 ; ++x )
	{
		for( int z=-18 ; z<11 ; ++z )
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
					scene.AddSceneObject(Entity::Sphere(position, radius, 
														std::make_unique<Asset::LambertianMaterial>(lambertianMaterial)));
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
#endif

	return scene;
}

static Entity::Camera SetupCamera()
{
	Tool::Vector3f position = {9.0f, 2.0f, 5.0f};
	Tool::Vector3f lookat = {0.0f, 0.0f, 0.0f};
	Tool::Vector3f up = {0.0f, 1.0f, 0.0f};
	float fov = 30.0f;
	float aperture = 0.1f;
	float focalOffset = 0.0f;
	float aspectRatio = OutputSize.X / (float)OutputSize.Y;

	return Entity::Camera(position, lookat, up, fov, aperture, focalOffset, aspectRatio);
}

int main()
{
	// Setup camera
	Entity::Camera camera = SetupCamera();

	// Setup scene
	Entity::Scene scene = CreateScene();

	// Render
	Gfx::Renderer renderer(OutputSize, AASampleCount);
	Utility::Texture renderTexture = renderer.RenderScene(scene, camera);

	renderTexture.Save(OutputFileName, 2.2f);

	return 0;
}
