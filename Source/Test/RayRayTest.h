#ifndef TEST__RAYRAY_TEST
#define TEST__RAYRAY_TEST

#include <Entity/Camera.h>
#include <Entity/Scene.h>
#include <Utility/Texture.h>
#include <functional>
#include <string>

namespace Test {

// Use this inside of each test classes' source file. Index must be continuous.
#define REGISTER_RAYRAYTEST(ClassName, Index) \
	static char dummyInit##ClassName = []() -> char { \
		Test::RayRayTest::RegisterSpawner({Index, #ClassName, []()->RayRayTest*{ return new ClassName(); }}); \
		return '\0'; \
	}()

class RayRayTest
{
public:
	struct Spawner;

public:
	RayRayTest();
	inline virtual ~RayRayTest() noexcept;

	static void RegisterSpawner(const Spawner& spawner);
	static const std::vector<RayRayTest::Spawner>& GetSpawners();

	Utility::Texture Run(const Tool::Vector2u& outputSize, size_t scatterDepth, size_t sampleCount, size_t threadCount, float gamma, float hdrExposure, size_t bloomSize);

private:
	virtual Entity::Scene SetupScene() = 0;
	virtual Entity::Camera SetupCamera(float aspectRatio) = 0;

private:
	Entity::Scene m_Scene;
	Entity::Camera m_Camera;

};

/***** IMPLEMENTATION *****/

struct RayRayTest::Spawner
{
	size_t Index;
	std::string Name;
	std::function<RayRayTest*()> Function;
};

inline RayRayTest::~RayRayTest() noexcept
{
}

} // namespace Test

#endif // TEST__RAYRAY_TEST
