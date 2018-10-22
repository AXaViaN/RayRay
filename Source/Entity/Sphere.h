#ifndef ENTITY__SPHERE
#define ENTITY__SPHERE

#include <Entity/SceneObject.h>
#include <Tool/Vector2.h>
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

	inline void Move(const MoveData& moveData);

	virtual bool CreateAABB(Tool::AABB& aabb, float startTime, float endTime) const override;
	virtual Tool::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const override;

private:
	Tool::Vector3f GetCurrentCenter(float time) const;
	void TestHitResult(Tool::HitResult& hitResult, const Tool::Ray& ray, float minT, float maxT) const;

	static Tool::Vector2f GetUV(const Tool::Vector3f& normal);

private:
	Tool::Vector3f m_Center;
	float m_Radius = 1.0f;

	MoveData m_MoveData;

};

/***** IMPLEMENTATION *****/

inline void Sphere::Move(const Sphere::MoveData& moveData)
{
	m_MoveData = moveData;
}

} // namespace Entity

#endif // ENTITY__SPHERE
