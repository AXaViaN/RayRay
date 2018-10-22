#include <Entity/Sphere.h>
#include <Tool/AABB.h>
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

bool Sphere::CreateAABB(Tool::AABB& aabb, float startTime, float endTime) const
{
	// SurroundingBox of the whole movement

	auto boxMin = GetCurrentCenter(startTime) - Tool::Vector3f(m_Radius, m_Radius, m_Radius);
	auto boxMax = GetCurrentCenter(startTime) + Tool::Vector3f(m_Radius, m_Radius, m_Radius);
	if(m_Radius < 0.0f)
	{
		std::swap(boxMin, boxMax);
	}
	auto box1 = Tool::AABB(boxMin, boxMax);

	boxMin = GetCurrentCenter(endTime) - Tool::Vector3f(m_Radius, m_Radius, m_Radius);
	boxMax = GetCurrentCenter(endTime) + Tool::Vector3f(m_Radius, m_Radius, m_Radius);
	if(m_Radius < 0.0f)
	{
		std::swap(boxMin, boxMax);
	}
	auto box2 = Tool::AABB(boxMin, boxMax);

	aabb = Tool::AABB(box1, box2);
	return true;
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
		hitResult.UV = GetUV(hitResult.Normal);
	}
}

Tool::Vector2f Sphere::GetUV(const Tool::Vector3f& normal)
{
	// phi angle is on XZ axis. Arctangent of z/x is in [-180, +180]
	float phi = Tool::Math::ArcTan(normal.Z, normal.X);
	// convert [-180, +180] -> [0, 1]
	phi = (phi + 180.0f) / 360.0f;

	// theta angle is vertical angle. Arctangent of y is in [-90, +90]
	float theta = Tool::Math::ArcSin(normal.Y);
	// convert [-90, +90] -> [0, 1]
	theta = (theta + 90.0f) / 180.0f;

	// We want the phi to rotate counter clockwise and theta to work top to bottom.
	// ArcTan makes phi clockwise and ArcSin makes theta bottom to top. So we use
	// (1 - angle) to convert them.
	return Tool::Vector2f{1.0f-phi, 1.0f-theta};
}

} // namespace Entity
