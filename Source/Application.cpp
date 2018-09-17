#include <Entity/Scene.h>
#include <Tool/Texture.h>
#include <Tool/RenderPlane.h>
#include <Utility/Color.h>
#include <Utility/Vector2.h>
#include <Utility/Vector3.h>
#include <Utility/Ray.h>
#include <string>

static const std::string OutputFileName = "output";
static constexpr Utility::Vector2u OutputSize = {200, 100};

static Utility::Color GetBackgroundColor(const Utility::Ray& ray)
{
	auto direction = ray.GetDirection().Normalized();
	float t = 0.5f * (direction.Y + 1.0f);

	auto colorVector = Utility::Vector3f(0.2f, 0.4f, 0.8f) * t +
					   Utility::Vector3f(1.0f, 1.0f, 1.0f) * (1.0f-t);

	return {colorVector.X, colorVector.Y, colorVector.Z};
}

static bool HitDetect(const Utility::Ray& ray, const Entity::Sphere& sphere)
{
	// If we want to check a point is on the sphere we can use: |P-C|=R
	// where P is the point, C is the sphere center, R is the sphere radius.
	// It can also be represented as (P-C)*(P-C)=R^2 where * means dot product.
	// When checking with a ray it becomes (P(t)-C)*(P(t)-C)=R^2
	// P(t)=S+Dt so it becomes (S+Dt-C)*(S+Dt-C)=R^2
	// Expand -> u=Dt, v=S-C -> (u+v)*(u+v)=R^2 -> u^2+2uv+v^2=R^2
	// Final version is t^2(D*D)+t(2D*(P-C))+(P-C)*(P-C)=R^2
	// Only variable thing is t. So it is a quadratic equation.
	// discriminant>0 means 2 intersection, discriminant=0 means 1, discriminant<0 means none

	auto sphereToRay = ray.GetOrigin() - sphere.Center;
	float a = ray.GetDirection().Dot(ray.GetDirection());
	float b = 2.0f * ray.GetDirection().Dot(sphereToRay);
	float c = sphereToRay.Dot(sphereToRay) - sphere.Radius*sphere.Radius;
	float discriminant = b*b - 4*a*c;
	return (discriminant > 0);
}

static Utility::Color GetColor(const Entity::Scene& scene, const Utility::Ray& ray)
{
	for( auto& sphere : scene.SphereList )
	{
		if(HitDetect(ray, sphere))
		{
			return sphere.Color;
		}
	}
	
	return GetBackgroundColor(ray);
}

int main()
{
	// Setup texture output
	Tool::Texture output(OutputFileName, OutputSize);
	
	// Setup render plane
	Tool::RenderPlane renderPlane({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, OutputSize.X/(float)OutputSize.Y);

	// Setup scene
	Entity::Scene scene;
	scene.SphereList.emplace_back(Entity::Sphere{Utility::Color{1, 0, 0}, { 0, 0, -1}, 0.5f});

	// Traverse from lower-left
	Utility::Vector2u position;
	for( position.Y=0 ; position.Y<OutputSize.Y ; ++position.Y )
	{
		for( position.X=0 ; position.X<OutputSize.X ; ++position.X )
		{
			Utility::Vector2f uv = {
				float(position.X) / float(OutputSize.X),
				float(position.Y) / float(OutputSize.Y)
			};

			auto rayHead = renderPlane.GetLowerLeft() + 
						   renderPlane.GetHorizontal()*uv.X + renderPlane.GetVertical()*uv.Y;
			auto rayDirection = rayHead - renderPlane.GetOrigin();

			Utility::Ray ray(renderPlane.GetOrigin(), rayDirection);
			Utility::Color color = GetColor(scene, ray);

			output.SetPixel(position, color);
		}
	}

	return 0;
}
