#include <Entity/Sphere.h>
#include <Tool/Ray.h>
#include <Tool/HitResult.h>
#include <Tool/Math.h>

namespace Entity {

Sphere::Sphere(const Tool::Vector3f& center, float radius, std::unique_ptr<Asset::Material>&& material) : 
	m_Center(center),
	m_Radius(radius)
{
	Material = std::move(material);
}

void Sphere::Move(const Tool::Vector3f& target, float t0, float t1)
{
	m_MoveData.Target = target;
	m_MoveData.StartTime = t0;
	m_MoveData.EndTime = t1;
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

	auto sphereToRay = ray.GetOrigin() - GetCurrentCenter(ray.GetFireTime());

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

Tool::Vector3f Sphere::GetCurrentCenter(float time) const
{
	if(m_MoveData.StartTime == m_MoveData.EndTime)
	{
		return m_Center;
	}

	float percentage = Tool::Math::Percentage(m_MoveData.StartTime, m_MoveData.EndTime, time);
	return Tool::Math::Lerp(m_Center, m_MoveData.Target, percentage);
}
void Sphere::TestHitResult(Tool::HitResult& hitResult, const Tool::Ray& ray, float minT, float maxT) const
{
	if(hitResult.T < maxT && 
	   hitResult.T > minT)
	{
		hitResult.IsHit = true;
		hitResult.Point = ray.GetPoint(hitResult.T);
		hitResult.Normal = (hitResult.Point - GetCurrentCenter(ray.GetFireTime())) / m_Radius;
	}
}

} // namespace Entity
