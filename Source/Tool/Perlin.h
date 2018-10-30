#ifndef TOOL__PERLIN
#define TOOL__PERLIN

#include <Tool/Random.h>
#include <Tool/Vector3.h>
#include <vector>

namespace Tool {

class Perlin
{
public:
	Perlin(Tool::Random& random=Tool::Random());

	float Noise(const Tool::Vector3f& point) const;
	float Turbulence(const Tool::Vector3f& point, unsigned int depth=7) const;

private:
	Tool::Vector3f SimpleNoise(const Tool::Vector3f& point) const;

private:
	std::vector<Tool::Vector3f> m_Data;
	std::vector<Tool::Vector3u> m_Permutation;

};

} // namespace Tool

#endif // TOOL__PERLIN
