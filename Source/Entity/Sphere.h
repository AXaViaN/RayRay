#ifndef ENTITY__SPHERE
#define ENTITY__SPHERE

#include <Entity/SceneObject.h>
#include <Tool/Vector3.h>

namespace Entity {

class Sphere : public Entity::SceneObject
{
public:
	Sphere(const Tool::Vector3f& center, float radius, std::unique_ptr<Asset::Material>&& material);

	virtual Tool::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const override;

private:
	void TestHitResult(Tool::HitResult& hitResult, const Tool::Ray& ray, float minT, float maxT) const;

	Tool::Vector3f m_Center;
	float m_Radius = 1.0f;

};

} // namespace Entity

#endif // ENTITY__SPHERE
