#include <Tool/Perlin.h>
#include <Tool/Math.h>

namespace Tool {

auto constexpr RandomQuality = 0x100u;

static float TrilinearInterpolation(Tool::Vector3f rawNoises[2][2][2], const Tool::Vector3f& point);

Perlin::Perlin(Tool::Random& random)
{
	m_Data.reserve(RandomQuality);
	m_Permutation.reserve(RandomQuality);
	for( auto i=0u ; i<RandomQuality ; ++i )
	{
		m_Data.emplace_back(Tool::Vector3f(random.GetFloat()*2.0f - 1.0f, 
										   random.GetFloat()*2.0f - 1.0f, 
										   random.GetFloat()*2.0f - 1.0f).Normalized());
		m_Permutation.emplace_back(Tool::Vector3u{i, i, i});
	}

	// Permutate
	for( auto i=RandomQuality-1u ; i>0 ; --i )
	{
		for( auto j=0 ; j<3 ; ++j )
		{
			auto current = i;
			auto target = static_cast<unsigned int>((current-1) * random.GetFloat());

			std::swap(m_Permutation[current][j], m_Permutation[target][j]);
		}
	}
}

float Perlin::Noise(const Tool::Vector3f& point) const
{
	auto nonDecimalOfPoint = Tool::Vector3f(Tool::Math::Floor(point.X), 
											Tool::Math::Floor(point.Y), 
											Tool::Math::Floor(point.Z));

	Tool::Vector3f rawNoises[2][2][2];
	for( auto i=0u ; i<2 ; ++i )
	{
		for( auto j=0u ; j<2 ; ++j )
		{
			for( auto k=0u ; k<2 ; ++k )
			{
				auto offset = Tool::Vector3f(static_cast<Tool::Vector3f::Type>(i), 
											 static_cast<Tool::Vector3f::Type>(j), 
											 static_cast<Tool::Vector3f::Type>(k));
				rawNoises[i][j][k] = SimpleNoise(nonDecimalOfPoint + offset);
			}
		}
	}

	auto decimalOfPoint = point - nonDecimalOfPoint;
	return TrilinearInterpolation(rawNoises, decimalOfPoint);
}
float Perlin::Turbulence(const Tool::Vector3f& point, unsigned int depth) const
{
	auto accumulation = 0.0f;

	auto tempPoint = point;
	auto weight = 1.0f;
	for( auto i=0u ; i<depth ; ++i )
	{
		accumulation += weight * Noise(tempPoint);
		tempPoint *= 2.0f;
		weight *= 0.5f;
	}

	return Tool::Math::Abs(accumulation);
}

Tool::Vector3f Perlin::SimpleNoise(const Tool::Vector3f& point) const
{
	auto idx = 0u;
	for( auto i=0u ; i<3 ; ++i )
	{
		auto target = static_cast<unsigned int>(point[i]) & (RandomQuality-1u);

		idx ^= m_Permutation[target][i];
	}

	return m_Data[idx];
}

/***** STATIC FUNCTIONS *****/

static float TrilinearInterpolation(Tool::Vector3f rawNoises[2][2][2], const Tool::Vector3f& point)
{
	// Hermite cubic (to fix mach bands)
	auto hermitePoint = point*point * (-point*2.0f + 3.0f);

	auto accumulation = 0.0f;
	for( auto i=0u ; i<2 ; ++i )
	{
		for( auto j=0u ; j<2 ; ++j )
		{
			for( auto k=0u ; k<2 ; ++k )
			{
				auto offset = Tool::Vector3f(static_cast<Tool::Vector3f::Type>(i), 
											 static_cast<Tool::Vector3f::Type>(j), 
											 static_cast<Tool::Vector3f::Type>(k));
				auto weight = point - offset;

				accumulation += (rawNoises[i][j][k].Dot(weight) * 
								 (i*hermitePoint.X + (1-i)*(1-hermitePoint.X)) * 
								 (j*hermitePoint.Y + (1-j)*(1-hermitePoint.Y)) * 
								 (k*hermitePoint.Z + (1-k)*(1-hermitePoint.Z)));
			}
		}
	}

	return accumulation;
}

} // namespace Tool
