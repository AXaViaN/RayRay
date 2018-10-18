#ifndef ENTITY__SCENE
#define ENTITY__SCENE

#include <Entity/SceneObject.h>
#include <vector>
#include <memory>

namespace Entity {
	class BVHNode;
}

namespace Entity {

class Scene : public Entity::SceneObject
{
public:
	inline Scene(float startTime, float endTime);

	virtual bool CreateAABB(Tool::AABB& aabb, float startTime, float endTime) const override;
	virtual Tool::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const override;

	template<typename T> inline void AddSceneObject(T&& object);
	template<typename T> inline void AddSceneObject(const T& object);

	Entity::BVHNode GetBVHRoot() const;

private:
	std::vector<std::shared_ptr<Entity::SceneObject>> m_SceneObjects;
	float m_StartTime;
	float m_EndTime;

};

/***** IMPLEMENTATION *****/

inline Scene::Scene(float startTime, float endTime) : 
	m_StartTime(startTime),
	m_EndTime(endTime)
{
}

template<typename T> inline void Scene::AddSceneObject(T&& object)
{
	m_SceneObjects.push_back(std::make_shared<T>(std::move(object)));
}
template<typename T> inline void Scene::AddSceneObject(const T& object)
{
	m_SceneObjects.push_back(std::make_shared<T>(object));
}

} // namespace Entity

#endif // ENTITY__SCENE
