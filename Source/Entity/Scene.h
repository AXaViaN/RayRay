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

	template<typename T> inline void AddSceneObject(T sceneObject);
	template<typename T, typename... Args> inline void AddSceneObject(Args... args);

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

template<typename T> inline void Scene::AddSceneObject(T sceneObject)
{
	m_SceneObjects.emplace_back(std::make_shared<T>(std::move(sceneObject)));
}
template<typename T, typename... Args> inline void Scene::AddSceneObject(Args... args)
{
	m_SceneObjects.emplace_back(std::make_shared<T>(args...));
}

} // namespace Entity

#endif // ENTITY__SCENE
