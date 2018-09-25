#include <Entity/Scene.h>
#include <Entity/Camera.h>
#include <Entity/Renderer.h>
#include <Entity/Sphere.h>
#include <Entity/LambertianMaterial.h>
#include <Entity/MetalMaterial.h>
#include <Entity/DielectricMaterial.h>
#include <Tool/Texture.h>
#include <Utility/Color.h>
#include <Utility/Vector2.h>
#include <Utility/Random.h>
#include <string>

static const std::string OutputFileName = "output";
static constexpr Utility::Vector2u OutputSize = {200, 100};
static constexpr size_t AASampleCount = 128;

static Entity::Scene CreateScene()
{
	Entity::Scene scene;
	Utility::Random random;

	Utility::Vector3f position;
	float radius;
	Entity::LambertianMaterial lambertianMaterial({});
	Entity::MetalMaterial metalMaterial({}, 0);
	Entity::DielectricMaterial dielectricMaterial(0);

	// Ground
	position = {0.0f, -1000.0f, 0.0f};
	radius = 1000.0f;
	lambertianMaterial = Entity::LambertianMaterial(Utility::Color{0.75f, 0.75f, 0.75f});
	scene.AddSceneObject(Entity::Sphere(position, radius, 
										std::make_unique<Entity::LambertianMaterial>(lambertianMaterial)));

	// Center
	position = {0.0f, 1.0f, 0.0f};
	radius = 1.0f;
	dielectricMaterial = Entity::DielectricMaterial(1.5f);
	scene.AddSceneObject(Entity::Sphere(position, radius, 
										std::make_unique<Entity::DielectricMaterial>(dielectricMaterial)));

	// Right metal
	position = {3.0f, 1.0f, 0.0f};
	radius = 1.0f;
	metalMaterial = Entity::MetalMaterial(Utility::Color{0.7f, 0.6f, 0.5f}, 0.0f);
	scene.AddSceneObject(Entity::Sphere(position, radius, 
										std::make_unique<Entity::MetalMaterial>(metalMaterial)));

	// Left glass
	position = {-3.0f, 1.0f, 0.0f};
	radius = 1.0f;
	dielectricMaterial = Entity::DielectricMaterial(1.5f);
	scene.AddSceneObject(Entity::Sphere(position, radius, 
										std::make_unique<Entity::DielectricMaterial>(dielectricMaterial)));
	position = {-3.0f, 1.0f, 0.0f};
	radius = -0.95f;
	dielectricMaterial = Entity::DielectricMaterial(1.5f);
	scene.AddSceneObject(Entity::Sphere(position, radius, 
										std::make_unique<Entity::DielectricMaterial>(dielectricMaterial)));

	// Left lambertian
	position = {-6.0f, 1.0f, 0.0f};
	radius = 1.0f;
	lambertianMaterial = Entity::LambertianMaterial(Utility::Color{0.2f, 0.4f, 0.8f});
	scene.AddSceneObject(Entity::Sphere(position, radius, 
										std::make_unique<Entity::LambertianMaterial>(lambertianMaterial)));

	// Random balls
#if 1
	radius = 0.2f;
	for( int x=-18 ; x<11 ; ++x )
	{
		for( int z=-18 ; z<11 ; ++z )
		{
			position = {x+0.9f*random.GetFloat(), radius, z+0.9f*random.GetFloat()};
			if((position-Utility::Vector3f(4.0f, radius, 0.0f)).Length() > 0.9f)
			{
				float chooseMaterial = random.GetFloat();
				if(chooseMaterial < 0.6f)
				{
					Utility::Color color{random.GetFloat()*random.GetFloat(), 
										 random.GetFloat()*random.GetFloat(), 
										 random.GetFloat()*random.GetFloat()};
					lambertianMaterial = Entity::LambertianMaterial(color);
					scene.AddSceneObject(Entity::Sphere(position, radius, 
														std::make_unique<Entity::LambertianMaterial>(lambertianMaterial)));
				}
				else if(chooseMaterial < 0.85f)
				{
					Utility::Color color{random.GetFloat()*random.GetFloat(), 
										 random.GetFloat()*random.GetFloat(), 
										 random.GetFloat()*random.GetFloat()};
					metalMaterial = Entity::MetalMaterial(color, 0.5f*random.GetFloat());
					scene.AddSceneObject(Entity::Sphere(position, radius, 
														std::make_unique<Entity::MetalMaterial>(metalMaterial)));
				}
				else
				{
					dielectricMaterial = Entity::DielectricMaterial(1.5f);
					scene.AddSceneObject(Entity::Sphere(position, radius, 
														std::make_unique<Entity::DielectricMaterial>(dielectricMaterial)));
				}
			}
		}
	}
#endif

	return scene;
}

static Entity::Camera SetupCamera()
{
	Utility::Vector3f position = {9.0f, 2.0f, 5.0f};
	Utility::Vector3f lookat = {0.0f, 0.0f, 0.0f};
	Utility::Vector3f up = {0.0f, 1.0f, 0.0f};
	float fov = 30.0f;
	float aperture = 0.1f;
	float aspectRatio = OutputSize.X / (float)OutputSize.Y;

	return Entity::Camera(position, lookat, up, fov, aperture, aspectRatio);
}

int main()
{
	// Setup camera
	Entity::Camera camera = SetupCamera();

	// Setup scene
	Entity::Scene scene = CreateScene();

	// Render
	Entity::Renderer renderer(OutputSize, AASampleCount);
	Tool::Texture renderTexture = renderer.RenderScene(scene, camera);

	renderTexture.Save(OutputFileName, 2.2f);

	return 0;
}
