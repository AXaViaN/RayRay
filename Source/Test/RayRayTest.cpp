#include <Test/RayRayTest.h>
#include <Gfx/Renderer.h>
#include <Gfx/PostProcess.h>
#include <Tool/Math.h>
#include <Utility/Texture.h>
#include <algorithm>

namespace Test {

static std::vector<RayRayTest::Spawner>& s_SpawnerList()
{
	static std::vector<RayRayTest::Spawner> spawners;
	return spawners;
}

RayRayTest::RayRayTest() : 
	m_Scene(0, 0),
	m_Camera({}, {}, {}, 0, 0, 0, 0, 0)
{
}

void RayRayTest::RegisterSpawner(const Spawner& spawner)
{
	auto& spawnerList = s_SpawnerList();
	spawnerList.emplace_back(spawner);
}
const std::vector<RayRayTest::Spawner>& RayRayTest::GetSpawners()
{
	auto& spawnerList = s_SpawnerList();
	std::sort(spawnerList.begin(), spawnerList.end(), 
			  [](const RayRayTest::Spawner& left, const RayRayTest::Spawner& right) -> bool 
			  {
					return left.Index < right.Index;
			  });

	return spawnerList;
}

Utility::Texture RayRayTest::Run(const Tool::Vector2u& outputSize, size_t scatterDepth, size_t sampleCount, size_t threadCount, float gamma, float hdrExposure, size_t bloomSize)
{
	float aspectRatio = outputSize.X / (float)outputSize.Y;

	// Setup camera
	Entity::Camera camera = SetupCamera(aspectRatio);

	// Setup scene
	Entity::Scene scene = SetupScene();

	// Render
	Gfx::Renderer renderer(outputSize, sampleCount, threadCount);
	Utility::Texture renderTexture = renderer.RenderScene(scene, camera, scatterDepth);

	// Post-processing
	{
		auto bloomScale = Tool::Math::Sqrt((outputSize.X * outputSize.Y) / 100000.0f);
		bloomSize = static_cast<size_t>(bloomSize * bloomScale);

		auto highlight = Gfx::PostProcess::GetLuminance(renderTexture);
		highlight = Gfx::PostProcess::GaussianBlur(highlight, bloomSize);
		renderTexture = Gfx::PostProcess::Bloom(renderTexture, highlight);
	}
	renderTexture = Gfx::PostProcess::HDRToneMap(renderTexture, hdrExposure);
	renderTexture = Gfx::PostProcess::GammaCorrection(renderTexture, gamma);

	return renderTexture;
}

} // namespace Test
