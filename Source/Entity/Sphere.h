#ifndef ENTITY__SPHERE
#define ENTITY__SPHERE

#include <Entity/SceneObject.h>
#include <Tool/Vector3.h>

namespace Entity {

class Sphere : public Entity::SceneObject
{
public:
	struct MoveData
	{
		Tool::Vector3f Target;
		float StartTime = 0.0f;
		float EndTime = 0.0f;
	};

public:
	Sphere(const Tool::Vector3f& center, float radius, std::unique_ptr<Asset::Material>&& material);

	void Move(const Tool::Vector3f& target, float t0, float t1);

	virtual Tool::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const override;

private:
	Tool::Vector3f GetCurrentCenter(float time) const;
	void TestHitResult(Tool::HitResult& hitResult, const Tool::Ray& ray, float minT, float maxT) const;

private:
	Tool::Vector3f m_Center;
	float m_Radius = 1.0f;

	MoveData m_MoveData;

};

} // namespace Entity

#endif // ENTITY__SPHERE
