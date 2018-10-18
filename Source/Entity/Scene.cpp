#include <Entity/Scene.h>
#include <Entity/BVHNode.h>
#include <Tool/AABB.h>
#include <Tool/Ray.h>
#include <Tool/HitResult.h>

namespace Entity {

bool Scene::CreateAABB(Tool::AABB& aabb, float startTime, float endTime) const
{
	if(m_SceneObjects.size() == 0)
	{
		return false;
	}

	Tool::AABB tempBox;
	if(m_SceneObjects[0]->CreateAABB(tempBox, startTime, endTime))
	{
		aabb = tempBox;
	}
	else
	{
		return false;
	}

	for( size_t i=1 ; i<m_SceneObjects.size() ; ++i )
	{
		auto& sceneObject = m_SceneObjects[i];

		if(sceneObject->CreateAABB(tempBox, startTime, endTime))
		{
			aabb = Tool::AABB(aabb, tempBox);
		}
		else
		{
			return false;
		}
	}

	return true;
}
Tool::HitResult Scene::HitCheck(const Tool::Ray& ray, float minT, float maxT) const
{
	Tool::HitResult bestHitResult;
	bestHitResult.T = maxT;

	for( auto& sceneObject : m_SceneObjects )
	{
		// Check until the best result. So the last one will be the closest object
		auto hitResult = sceneObject->HitCheck(ray, minT, bestHitResult.T);
		if(hitResult.IsHit)
		{
			bestHitResult = hitResult;
		}
	}

	return bestHitResult;
}

Entity::BVHNode Scene::GetBVHRoot() const
{
	return Entity::BVHNode(m_SceneObjects, m_StartTime, m_EndTime);
}

} // namespace Entity
