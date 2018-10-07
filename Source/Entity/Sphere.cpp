#include <Entity/Sphere.h>
#include <Tool/Ray.h>
#include <Tool/HitResult.h>

namespace Entity {

Sphere::Sphere(const Tool::Vector3f& center, float radius, std::unique_ptr<Asset::Material>&& material) : 
	m_Center(center),
	m_Radius(radius)
{
	Material = std::move(material);
}

Tool::HitResult Sphere::HitCheck(const Tool::Ray& ray, float minT, float maxT) const
{
	Tool::HitResult hitResult;
	hitResult.Object = this;

	// If we want to check if a point is on the sphere we can use: |P-C|=R
	// where P is the point, C is the sphere center, R is the sphere radius.
	// It can also be represented as (P-C)*(P-C)=R^2 where * means dot product.
	// When checking with a ray it becomes (P(t)-C)*(P(t)-C)=R^2
	// P(t)=S+Dt so it becomes (S+Dt-C)*(S+Dt-C)=R^2
	// Expand -> u=Dt, v=S-C -> (u+v)*(u+v)=R^2 -> u^2+2uv+v^2=R^2
	// Final version is t^2(D*D)+t(2D*(P-C))+(P-C)*(P-C)=R^2
	// Only variable thing is t. So it is a quadratic equation.
	// discriminant>0 means 2 intersection, discriminant=0 means 1, discriminant<0 means none

	auto sphereToRay = ray.GetOrigin() - m_Center;

	float a = ray.GetDirection().Dot(ray.GetDirection());
	float b = 2.0f * ray.GetDirection().Dot(sphereToRay);
	float c = sphereToRay.Dot(sphereToRay) - m_Radius*m_Radius;
	float discriminant = b*b - 4*a*c;

	if(discriminant > 0)
	{
		// Test the small t (closer point)
		hitResult.T = (-b - std::sqrtf(discriminant)) / (2.0f*a);
		TestHitResult(hitResult, ray, minT, maxT);

		if(hitResult.IsHit == false)
		{
			// Test the other t
			hitResult.T = (-b + std::sqrtf(discriminant)) / (2.0f*a);
			TestHitResult(hitResult, ray, minT, maxT);
		}
	}

	return hitResult;
}

void Sphere::TestHitResult(Tool::HitResult& hitResult, const Tool::Ray& ray, float minT, float maxT) const
{
	if(hitResult.T < maxT && 
	   hitResult.T > minT)
	{
		hitResult.IsHit = true;
		hitResult.Point = ray.GetPoint(hitResult.T);
		hitResult.Normal = (hitResult.Point - m_Center) / m_Radius;
	}
}

} // namespace Entity
