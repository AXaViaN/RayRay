#include <Entity/Scene.h>

namespace Entity {

Utility::HitResult Scene::HitCheck(const Utility::Ray& ray, float minT, float maxT) const
{
	Utility::HitResult bestHitResult;
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
