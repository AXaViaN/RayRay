#ifndef ENTITY__SCENE
#define ENTITY__SCENE

#include <Entity/SceneObject.h>
#include <vector>
#include <memory>

namespace Entity {

class Scene : public Entity::SceneObject
{
public:
	virtual Utility::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const override;

	template<typename T> inline void AddSceneObject(const T& object);
	template<typename T> inline void AddSceneObject(T&& object);

private:
	std::vector<std::unique_ptr<Entity::SceneObject>> m_SceneObjects;

};

template<typename T> inline void Scene::AddSceneObject(const T& object)
{
	m_SceneObjects.push_back(std::make_unique<T>(object));
}
template<typename T> inline void Scene::AddSceneObject(T&& object)
{
	m_SceneObjects.push_back(std::make_unique<T>(std::move(object)));
}

} // namespace Entity

#endif // ENTITY__SCENE

