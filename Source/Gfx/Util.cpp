#include <Gfx/Util.h>
#include <Tool/Random.h>
#include <Tool/Math.h>

namespace Gfx {

Tool::Vector3f Util::GetRandomVectorInUnitSphere()
{
	Tool::Vector3f point = {1.0f, 1.0f, 1.0f};
	while(point.SquaredLength() >= 1.0f)
	{
		// Random vector
		point = {
			Tool::Random::Instance().GetFloat(), 
			Tool::Random::Instance().GetFloat(), 
			Tool::Random::Instance().GetFloat()
		};
		// [0,1) -> (-1,+1)
		point = (point * 2.0f) - Tool::Vector3f{1.0f, 1.0f, 1.0f};
	}
	return point;
}
Tool::Vector3f Util::GetRandomVectorInUnitDisk()
{
	Tool::Vector3f point = {1.0f, 1.0f, 0.0f};
	while(point.SquaredLength() >= 1.0f)
	{
		// Random vector
		point = {
			Tool::Random::Instance().GetFloat(), 
			Tool::Random::Instance().GetFloat(), 
			0.0f
		};
		// [0,1) -> (-1,+1)
		point = (point * 2.0f) - Tool::Vector3f{1.0f, 1.0f, 0.0f};
	}
	return point;
}

Tool::Vector2f Util::GetSphericalUV(const Tool::Vector3f& normal)
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

Tool::Vector3f Util::Reflect(const Tool::Vector3f& vector, const Tool::Vector3f& normal)
{
	return vector - (normal * vector.Dot(normal) * 2.0f);
}
Tool::Vector3f Util::Refract(const Tool::Vector3f& vector, const Tool::Vector3f& normal, float N1OverN2)
{
	// Snell's law: N1 * sin(thetaN1) = N2 * sin(thetaN2)
	// sin^2(x) + cos^2(x) = 1
	// sin^2(thetaN2) = (N1/N2)^2 * sin^2(thetaN1)

	float cos_ThetaN1 = vector.Dot(normal);
	float sin2_ThetaN1 = 1.0f - cos_ThetaN1*cos_ThetaN1;
	float sin2_ThetaN2 = N1OverN2*N1OverN2 * sin2_ThetaN1;
	float cos2_ThetaN2 = 1.0f - sin2_ThetaN2;

	Tool::Vector3f refraction;
	if(cos2_ThetaN2 > 0)
	{
		Tool::Vector3f vectorX = vector - normal*cos_ThetaN1;

		Tool::Vector3f refractionX = vectorX * N1OverN2;
		Tool::Vector3f refractionY = -normal * std::sqrtf(cos2_ThetaN2);

		refraction = (refractionX + refractionY).Normalized();
	}
	return refraction;
}

float Util::FresnelSchlick(float cosine, float refractiveIndex)
{
	// r0 = ((n1-n2)/(n1+n2))^2
	float r0 = (1.0f - refractiveIndex) / (1.0f + refractiveIndex);
	r0 = r0*r0;

	// Schlick's reflection coefficient approximation
	return (r0 + (1.0f-r0)*std::powf(1.0f-cosine, 5.0f));
}

} // namespace Gfx
