#include <Entity/Scene.h>
#include <Tool/Ray.h>
#include <Tool/HitResult.h>

namespace Entity {

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

} // namespace Entity
