#include <Entity/Renderer.h>
#include <Tool/Ray.h>
#include <Utility/Vector3.h>
#include <thread>
#include <mutex>

namespace Entity {

struct SampleData
{
	const Entity::Scene& Scene;
	const Entity::Camera& Camera;

	std::vector<Tool::Texture>& SampleTextures;
	std::mutex& SampleMutex;

	Utility::Vector2u TextureSize;
	Utility::Vector2f UVOffset;
};

static void GetSampleTexture(const SampleData& sampleData);
static Utility::Color GetColor(const Entity::Scene& scene, const Tool::Ray& ray);
static Utility::Color GetBackgroundColor(const Tool::Ray& ray);

Renderer::Renderer(const Utility::Vector2u& outputSize, size_t aaSampleCount) : 
	m_OutputSize(outputSize),
	m_AASampleCount(aaSampleCount)
{
}

Tool::Texture Renderer::RenderScene(const Entity::Scene& scene, const Entity::Camera& camera) const
{
	Utility::Vector2u aaSampleSize;
	aaSampleSize.X = (size_t)std::sqrtf((float)m_AASampleCount);
	aaSampleSize.Y = (size_t)(m_AASampleCount / aaSampleSize.X);
	size_t aaSampleCount = aaSampleSize.X * aaSampleSize.Y;

	std::vector<Tool::Texture> sampleTextures;
	std::mutex sampleMutex;

	// Get samples
	std::vector<std::thread> threads;
	SampleData sampleData = {scene, camera, sampleTextures, sampleMutex, m_OutputSize};
	Utility::Vector2u aaSample;
	for( aaSample.Y=0 ; aaSample.Y<aaSampleSize.Y ; ++aaSample.Y )
	{
		for( aaSample.X=0 ; aaSample.X<aaSampleSize.X ; ++aaSample.X )
		{
			sampleData.UVOffset = {
				float(aaSample.X) / float(aaSampleSize.X),
				float(aaSample.Y) / float(aaSampleSize.Y)
			};

			threads.emplace_back(GetSampleTexture, sampleData);
		}
	}
	for( auto& thread : threads )
	{
		thread.join();
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

static void GetSampleTexture(const SampleData& sampleData)
{
	Tool::Texture sample(sampleData.TextureSize);

	// Traverse from lower-left
	Utility::Vector2u position;
	for( position.Y=0 ; position.Y<sampleData.TextureSize.Y ; ++position.Y )
	{
		for( position.X=0 ; position.X<sampleData.TextureSize.X ; ++position.X )
		{
			Utility::Vector2f uv = {
				float(position.X + sampleData.UVOffset.X) / float(sampleData.TextureSize.X),
				float(position.Y + sampleData.UVOffset.Y) / float(sampleData.TextureSize.Y)
			};

			Tool::Ray ray = sampleData.Camera.GetRay(uv);
			Utility::Color color = GetColor(sampleData.Scene, ray);

			sample.SetPixel(position, color);
		}
	}

	std::unique_lock<std::mutex> lock(sampleData.SampleMutex);
	sampleData.SampleTextures.emplace_back(sample);
}

static Utility::Color GetColor(const Entity::Scene& scene, const Tool::Ray& ray)
{
	auto hitResult = scene.HitCheck(ray, 0.0f, std::numeric_limits<float>::max());
	if(hitResult.IsHit)
	{
		// Render normals for testing
		Utility::Vector3f normal = hitResult.Normal;

		// [-1,+1] -> [0,1]
		normal += {1, 1, 1};
		normal /= 2;

		return {normal.X, normal.Y, normal.Z};
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
