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

	std::vector<Tool::Texture>& SampleTextures;
	std::mutex& SampleMutex;

	Utility::Vector2u TextureSize;
	Utility::Vector2f UVOffset;
};

static void GetSampleTexture(const SampleData& data);
static Utility::Vector3f GetRandomVectorInUnitSphere();
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
	aaSampleSize.X = (unsigned int)std::sqrtf((float)m_AASampleCount);
	aaSampleSize.Y = (unsigned int)(m_AASampleCount / aaSampleSize.X);
	size_t aaSampleCount = aaSampleSize.X * aaSampleSize.Y;

	std::vector<Tool::Texture> sampleTextures;
	std::mutex sampleMutex;

	// Get samples
	constexpr size_t ThreadCount = 5;
	std::thread threads[ThreadCount];
	size_t threadIdx = 0;
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
			Utility::Color color = GetColor(data.Scene, ray);

			sample.SetPixel(position, color);
		}
	}

	std::unique_lock<std::mutex> lock(data.SampleMutex);
	data.SampleTextures.emplace_back(sample);
}

static Utility::Vector3f GetRandomVectorInUnitSphere()
{
	Utility::Vector3f point = {1.0f, 1.0f, 1.0f};
	while(point.SquaredLength() >= 1.0f)
	{
		// Random vector
		point = {s_Random.GetFloat(), s_Random.GetFloat(), s_Random.GetFloat()};
		// [0,1) -> (-1,+1)
		point = (point * 2.0f) - Utility::Vector3f{1.0f, 1.0f, 1.0f};
	}
	return point;
}
static Utility::Color GetColor(const Entity::Scene& scene, const Tool::Ray& ray)
{
	auto hitResult = scene.HitCheck(ray, 0.001f, std::numeric_limits<float>::max());
	if(hitResult.IsHit)
	{
		// Select a random reflection direction
		auto target = hitResult.Point + hitResult.Normal + GetRandomVectorInUnitSphere();
		auto targetDirection = (target - hitResult.Point).Normalized();

		// Get reflection color
		auto reflectedRay = Tool::Ray(hitResult.Point, targetDirection);
		auto reflectionColor = GetColor(scene, reflectedRay);

		// Combine colors
		Utility::Color color = {
			hitResult.Object->Color.R * reflectionColor.R * (1.0f - hitResult.Object->Absorption),
			hitResult.Object->Color.G * reflectionColor.G * (1.0f - hitResult.Object->Absorption),
			hitResult.Object->Color.B * reflectionColor.B * (1.0f - hitResult.Object->Absorption)
		};

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
