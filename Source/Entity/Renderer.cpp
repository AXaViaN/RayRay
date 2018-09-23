#include <Entity/Renderer.h>
#include <Tool/Ray.h>
#include <Utility/Vector3.h>
#include <Utility/Random.h>
#include <thread>
#include <mutex>

namespace Entity {

static Utility::Random s_Random;

struct SampleData
{
	const Entity::Scene& Scene;
	const Entity::Camera& Camera;
	const size_t ScatterDepth;

	std::vector<Tool::Texture>& SampleTextures;
	std::mutex& SampleMutex;

	Utility::Vector2u TextureSize;
	Utility::Vector2f UVOffset;
};

static void GetSampleTexture(const SampleData& data);
static Utility::Color GetColor(const Entity::Scene& scene, const Tool::Ray& ray, size_t scatterDepth);
static Utility::Color GetBackgroundColor(const Tool::Ray& ray);

Renderer::Renderer(const Utility::Vector2u& outputSize, size_t aaSampleCount) : 
	m_OutputSize(outputSize),
	m_AASampleCount(aaSampleCount)
{
}

Tool::Texture Renderer::RenderScene(const Entity::Scene& scene, const Entity::Camera& camera, size_t scatterDepth) const
{
	Utility::Vector2u aaSampleSize;
	aaSampleSize.X = (unsigned int)std::sqrtf((float)m_AASampleCount);
	aaSampleSize.Y = (unsigned int)(m_AASampleCount / aaSampleSize.X);
	size_t aaSampleCount = aaSampleSize.X * aaSampleSize.Y;

	std::vector<Tool::Texture> sampleTextures;
	std::mutex sampleMutex;

	// Get samples
	constexpr size_t ThreadCount = 5;
	std::thread threads[ThreadCount];
	size_t threadIdx = 0;
	SampleData sampleData = {scene, camera, scatterDepth, sampleTextures, sampleMutex, m_OutputSize};
	Utility::Vector2u aaSample;
	for( aaSample.Y=0 ; aaSample.Y<aaSampleSize.Y ; ++aaSample.Y )
	{
		for( aaSample.X=0 ; aaSample.X<aaSampleSize.X ; ++aaSample.X )
		{
			sampleData.UVOffset = {
				float(aaSample.X) / float(aaSampleSize.X),
				float(aaSample.Y) / float(aaSampleSize.Y)
			};

			if(threadIdx >= ThreadCount)
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

	// Avarage samples
	Tool::Texture output(m_OutputSize);
	Utility::Vector2u position;
	for( position.Y=0 ; position.Y<m_OutputSize.Y ; ++position.Y )
	{
		for( position.X=0 ; position.X<m_OutputSize.X ; ++position.X )
		{
			Utility::Color color;
			for( auto& sampleTexture : sampleTextures )
			{
				Utility::Color sampleColor = sampleTexture.GetPixel(position);
				color.R += sampleColor.R;
				color.G += sampleColor.G;
				color.B += sampleColor.B;
			}
			color.R /= static_cast<float>(aaSampleCount);
			color.G /= static_cast<float>(aaSampleCount);
			color.B /= static_cast<float>(aaSampleCount);

			output.SetPixel(position, color);
		}
	}

	return output;
}

static void GetSampleTexture(const SampleData& data)
{
	Tool::Texture sample(data.TextureSize);

	// Traverse from lower-left
	Utility::Vector2u position;
	for( position.Y=0 ; position.Y<data.TextureSize.Y ; ++position.Y )
	{
		for( position.X=0 ; position.X<data.TextureSize.X ; ++position.X )
		{
			Utility::Vector2f uv = {
				float(position.X + data.UVOffset.X) / float(data.TextureSize.X),
				float(position.Y + data.UVOffset.Y) / float(data.TextureSize.Y)
			};

			Tool::Ray ray = data.Camera.GetRay(uv);
			Utility::Color color = GetColor(data.Scene, ray, data.ScatterDepth);

			sample.SetPixel(position, color);
		}
	}

	std::unique_lock<std::mutex> lock(data.SampleMutex);
	data.SampleTextures.emplace_back(sample);
}

static Utility::Color GetColor(const Entity::Scene& scene, const Tool::Ray& ray, size_t scatterDepth)
{
	// Hit the ray to a scene object
	auto hitResult = scene.HitCheck(ray, 0.001f, std::numeric_limits<float>::max());
	if(hitResult.IsHit)
	{
		Utility::Color color;
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
static Utility::Color GetBackgroundColor(const Tool::Ray& ray)
{
	auto direction = ray.GetDirection().Normalized();
	float t = 0.5f * (direction.Y + 1.0f);

	auto colorVector = Utility::Vector3f(0.2f, 0.4f, 0.8f) * t +
					   Utility::Vector3f(1.0f, 1.0f, 1.0f) * (1.0f-t);

	return {colorVector.X, colorVector.Y, colorVector.Z};
}

} // namespace Entity
