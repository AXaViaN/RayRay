#ifndef ENTITY__BVH_NODE
#define ENTITY__BVH_NODE

#include <Entity/SceneObject.h>
#include <Tool/AABB.h>
#include <vector>
#include <memory>

namespace Entity {

class BVHNode : public Entity::SceneObject
{
public:
	inline BVHNode();
	BVHNode(const std::vector<std::shared_ptr<Entity::SceneObject>>& sceneObjects, 
			float startTime, float endTime);

	virtual bool CreateAABB(Tool::AABB& aabb, float startTime, float endTime) const override;
	virtual Tool::HitResult HitCheck(const Tool::Ray& ray, float minT, float maxT) const override;

private:
	void CreateNode(std::vector<std::shared_ptr<Entity::SceneObject>>& sceneObjects, 
					size_t startIdx, size_t size, 
					float startTime, float endTime);

private:
	Tool::AABB m_AABB;

	std::shared_ptr<Entity::SceneObject> m_LeftNode;
	std::shared_ptr<Entity::SceneObject> m_RightNode;

};

/***** IMPLEMENTATION *****/

inline BVHNode::BVHNode()
{
}

} // namespace Entity

#endif // ENTITY__BVH_NODE
