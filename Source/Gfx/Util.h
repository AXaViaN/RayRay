#ifndef GFX__UTIL
#define GFX__UTIL

#include <Tool/Vector2.h>
#include <Tool/Vector3.h>

namespace Gfx {

class Util
{
public:
	static Tool::Vector3f GetRandomVectorInUnitSphere();
	static Tool::Vector3f GetRandomVectorInUnitDisk();

	static Tool::Vector2f GetSphericalUV(const Tool::Vector3f& normal);

	static Tool::Vector3f Reflect(const Tool::Vector3f& vector, const Tool::Vector3f& normal);
	/*
	 *	@returns zero vector if there is no refraction
	 */
	static Tool::Vector3f Refract(const Tool::Vector3f& vector, const Tool::Vector3f& normal, float N1OverN2);

	static float FresnelSchlick(float cosine, float refractiveIndex);

};

} // namespace Gfx

#endif // GFX__UTIL
