#include <Gfx/Renderer.h>
#include <Entity/Camera.h>
#include <Entity/Scene.h>
#include <Tool/Ray.h>
#include <Tool/HitResult.h>
#include <Tool/ScatterResult.h>
#include <Tool/Vector3.h>
#include <Utility/Texture.h>
#include <thread>
#include <mutex>

namespace Gfx {

struct SampleData
{
	const Entity::Scene& Scene;
	const Entity::Camera& Camera;
	const size_t ScatterDepth;

	Utility::Texture& OutputTexture;
	std::mutex& OutputMutex;
	size_t SampleCount;

	Tool::Vector2u TextureSize;
	Tool::Vector2f UVOffset;
};

static void GetSampleTexture(const SampleData& data);
static Tool::Color GetColor(const Entity::Scene& scene, const Tool::Ray& ray, size_t scatterDepth);
static Tool::Color GetBackgroundColor(const Tool::Ray& ray);

Renderer::Renderer(const Tool::Vector2u& outputSize, size_t sampleCount, size_t threadCount) : 
	m_OutputSize(outputSize),
	m_SampleCount(sampleCount),
	m_ThreadCount(threadCount)
{
}

Utility::Texture Renderer::RenderScene(const Entity::Scene& scene, const Entity::Camera& camera, size_t scatterDepth) const
{
	Tool::Vector2u sampleSize = {
		(unsigned int)std::sqrtf((float)m_SampleCount),
		(unsigned int)(m_SampleCount / sampleSize.X)
	};
	size_t sampleCount = sampleSize.X * sampleSize.Y;

	Utility::Texture output(m_OutputSize);
	std::mutex outputMutex;

	// Get samples
	std::vector<std::thread> threads(m_ThreadCount);
	size_t threadIdx = 0;
	SampleData sampleData = {scene, camera, scatterDepth, output, outputMutex, sampleCount, m_OutputSize};
	Tool::Vector2u sampleOffset;
	for( sampleOffset.Y=0 ; sampleOffset.Y<sampleSize.Y ; ++sampleOffset.Y )
	{
		for( sampleOffset.X=0 ; sampleOffset.X<sampleSize.X ; ++sampleOffset.X )
		{
			sampleData.UVOffset = {
				float(sampleOffset.X) / float(sampleSize.X),
				float(sampleOffset.Y) / float(sampleSize.Y)
			};

			if(threadIdx >= m_ThreadCount)
			{
				threadIdx = 0;
			}
			if(threads[threadIdx].joinable())
			{
				threads[threadIdx].join();
			}

			threads[threadIdx++] = std::thread(GetSampleTexture, sampleData);
		}
	}
	for( auto& thread : threads )
	{
		if(thread.joinable())
		{
			thread.join();
		}
	}

	return output;
}

/***** STATIC FUNCTIONS *****/

static void GetSampleTexture(const SampleData& data)
{
	// Traverse from lower-left
	Tool::Vector2u position;
	for( position.Y=0 ; position.Y<data.TextureSize.Y ; ++position.Y )
	{
		for( position.X=0 ; position.X<data.TextureSize.X ; ++position.X )
		{
			Tool::Vector2f uv = {
				float(position.X + data.UVOffset.X) / float(data.TextureSize.X),
				float(position.Y + data.UVOffset.Y) / float(data.TextureSize.Y)
			};

			Tool::Ray ray = data.Camera.GetRay(uv);
			Tool::Color color = GetColor(data.Scene, ray, data.ScatterDepth);

			std::unique_lock<std::mutex> lock(data.OutputMutex);
			auto currentColor = data.OutputTexture.GetPixel(position);
			Tool::Color outputColor = {
				currentColor.R + (color.R / static_cast<float>(data.SampleCount)),
				currentColor.G + (color.G / static_cast<float>(data.SampleCount)),
				currentColor.B + (color.B / static_cast<float>(data.SampleCount))
			};
			data.OutputTexture.SetPixel(position, outputColor);
		}
	}
}

static Tool::Color GetColor(const Entity::Scene& scene, const Tool::Ray& ray, size_t scatterDepth)
{
	// Hit the ray to a scene object
	auto hitResult = scene.HitCheck(ray, 0.001f, std::numeric_limits<float>::max());
	if(hitResult.IsHit)
	{
		Tool::Color color;
		if(hitResult.Object->Material != nullptr &&
		   scatterDepth > 0)
		{
			// Scatter from the object
			auto scatterResult = hitResult.Object->Material->ScatterCheck(ray, hitResult);
			if(scatterResult.IsScatter)
			{
				auto scatterColor = GetColor(scene, scatterResult.ScatterRay, scatterDepth-1);

				color = {scatterResult.ObjectColor.R * scatterColor.R,
						 scatterResult.ObjectColor.G * scatterColor.G,
						 scatterResult.ObjectColor.B * scatterColor.B};
			}
		}

		return color;
	}

	return GetBackgroundColor(ray);
}
static Tool::Color GetBackgroundColor(const Tool::Ray& ray)
{
	auto direction = ray.GetDirection().Normalized();
	float t = 0.5f * (direction.Y + 1.0f);

	auto colorVector = Tool::Vector3f(0.2f, 0.4f, 0.8f) * t +
					   Tool::Vector3f(1.0f, 1.0f, 1.0f) * (1.0f-t);

	return {colorVector.X, colorVector.Y, colorVector.Z};
}

} // namespace Gfx
