#ifndef UTILITY__RANDOM
#define UTILITY__RANDOM

#include <random>

namespace Utility {

class Random
{
public:
	inline Random();
	inline Random(unsigned int seed);

	inline void Seed(unsigned int seed);
	inline unsigned int GetLastSeed() const;

	inline float GetFloat();
	inline float GetFloat(float min, float max);
	inline int GetInt();
	inline int GetInt(int min, int max);

private:
	std::default_random_engine m_RandomEngine;
	std::uniform_real_distribution<float> m_Distribution;

	unsigned int m_LastSeed = 0;

};

inline Random::Random()
{
	Seed(std::random_device()());
}
inline Random::Random(unsigned int seed)
{
	Seed(seed);
}

inline void Random::Seed(unsigned int seed)
{
	m_RandomEngine.seed(seed);
	m_LastSeed = seed;
}
inline unsigned int Random::GetLastSeed() const
{
	return m_LastSeed;
}

inline float Random::GetFloat()
{
	return m_Distribution(m_RandomEngine);
}
inline float Random::GetFloat(float min, float max)
{
	return min + GetFloat()*(max-min);
}
inline int Random::GetInt()
{
	return GetInt(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}
inline int Random::GetInt(int min, int max)
{
	return static_cast<int>(GetFloat(static_cast<float>(min), static_cast<float>(max)));
}

} // namespace Utility

#endif // UTILITY__RANDOM
