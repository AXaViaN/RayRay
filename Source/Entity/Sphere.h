#ifndef ENTITY__SPHERE
#define ENTITY__SPHERE

#include <Entity/SceneObject.h>

namespace Entity {

class Sphere : public Entity::SceneObject
{
public:
	inline Sphere(const Utility::Color& color, const Utility::Vector3f& center, float radius);

	virtual Utility::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const override;

private:
	void TestHitResult(Utility::HitResult& hitResult, const Tool::Ray& ray, float minT, float maxT) const;

	Utility::Vector3f m_Center;
	float m_Radius = 1.0f;

};

inline Sphere::Sphere(const Utility::Color& color, const Utility::Vector3f& center, float radius) : 
	m_Center(center),
	m_Radius(radius)
{
	Color = color;
}

} // namespace Entity

#endif // ENTITY__SPHERE
