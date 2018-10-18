#include <Entity/BVHNode.h>
#include <Tool/HitResult.h>
#include <Tool/Random.h>

namespace Entity {

static void LogError(const std::string& message)
{
	std::printf("Error: %s\n", message.c_str());
	std::getchar();
}

static int CompareBox(const void* left, const void* right, int axisIdx);
static int CompareBoxInX(const void* left, const void* right);
static int CompareBoxInY(const void* left, const void* right);
static int CompareBoxInZ(const void* left, const void* right);

BVHNode::BVHNode(const std::vector<std::shared_ptr<Entity::SceneObject>>& sceneObjects, float startTime, float endTime)
{
	auto sceneObjectsCopy = sceneObjects;
	CreateNode(sceneObjectsCopy, 0, sceneObjectsCopy.size(), startTime, endTime);
}

bool BVHNode::CreateAABB(Tool::AABB& aabb, float startTime, float endTime) const
{
	aabb = m_AABB;
	return true;
}
Tool::HitResult BVHNode::HitCheck(const Tool::Ray& ray, float minT, float maxT) const
{
	if(m_AABB.Hit(ray, minT, maxT) == false)
	{
		return Tool::HitResult();
	}

	Tool::HitResult leftHitResult = m_LeftNode->HitCheck(ray, minT, maxT);
	Tool::HitResult rightHitResult = m_RightNode->HitCheck(ray, minT, maxT);
	if(leftHitResult.IsHit && rightHitResult.IsHit)
	{
		if(leftHitResult.T < rightHitResult.T)
		{
			return leftHitResult;
		}
		else
		{
			return rightHitResult;
		}
	}
	else if(leftHitResult.IsHit)
	{
		return leftHitResult;
	}
	else if(rightHitResult.IsHit)
	{
		return rightHitResult;
	}
	else
	{
		return Tool::HitResult();
	}
}

void BVHNode::CreateNode(std::vector<std::shared_ptr<Entity::SceneObject>>& sceneObjects, size_t startIdx, size_t size, float startTime, float endTime)
{
	if(size == 0)
	{
		return;
	}

	// Sort scene objects
	int axis = Tool::Random::Instance().GetInt(0, 3);
	if(axis == 0)
	{
		std::qsort(sceneObjects.data()+startIdx, size, sizeof(std::shared_ptr<Entity::SceneObject>), 
				   CompareBoxInX);
	}
	else if(axis == 1)
	{
		std::qsort(sceneObjects.data()+startIdx, size, sizeof(std::shared_ptr<Entity::SceneObject>), 
				   CompareBoxInY);
	}
	else
	{
		std::qsort(sceneObjects.data()+startIdx, size, sizeof(std::shared_ptr<Entity::SceneObject>), 
				   CompareBoxInZ);
	}

	// Assign child nodes
	if(size == 1)
	{
		m_LeftNode = sceneObjects[startIdx];
		m_RightNode = sceneObjects[startIdx];
	}
	else if(size == 2)
	{
		m_LeftNode = sceneObjects[startIdx];
		m_RightNode = sceneObjects[startIdx + 1];
	}
	else
	{
		auto newNode = std::make_shared<BVHNode>();
		newNode->CreateNode(sceneObjects, startIdx, size/2, startTime, endTime);
		m_LeftNode = newNode;

		newNode = std::make_shared<BVHNode>();
		newNode->CreateNode(sceneObjects, startIdx+(size/2), size-(size/2), startTime, endTime);
		m_RightNode = newNode;
	}

	// SurroundingBox of the child nodes
	Tool::AABB leftAABB;
	Tool::AABB rightAABB;
	if(m_LeftNode->CreateAABB(leftAABB, startTime, endTime) == false || 
	   m_RightNode->CreateAABB(rightAABB, startTime, endTime) == false)
	{
		LogError("No bounding box available!");
	}

	m_AABB = Tool::AABB(leftAABB, rightAABB);
}

/***** STATIC FUNCTIONS *****/

static int CompareBox(const void* left, const void* right, int axisIdx)
{
	auto leftNode = *reinterpret_cast<const std::shared_ptr<Entity::SceneObject>*>(left);
	auto rightNode = *reinterpret_cast<const std::shared_ptr<Entity::SceneObject>*>(right);

	Tool::AABB leftAABB;
	Tool::AABB rightAABB;
	if(leftNode->CreateAABB(leftAABB, 0, 0) == false || 
	   rightNode->CreateAABB(rightAABB, 0, 0) == false)
	{
		LogError("No bounding box available!");
	}

	if(rightAABB.IsSmallerOnAxis(leftAABB, axisIdx))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
static int CompareBoxInX(const void* left, const void* right)
{
	return CompareBox(left, right, 0);
}
static int CompareBoxInY(const void* left, const void* right)
{
	return CompareBox(left, right, 1);
}
static int CompareBoxInZ(const void* left, const void* right)
{
	return CompareBox(left, right, 2);
}

} // namespace Entity
