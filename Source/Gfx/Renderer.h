#ifndef GFX__RENDERER
#define GFX__RENDERER

#include <Tool/Vector2.h>

namespace Entity {
	class Camera;
	class Scene;
}
namespace Utility {
	class Texture;
}

namespace Gfx {

class Renderer
{
public:
	Renderer(const Tool::Vector2u& outputSize, size_t sampleCount, size_t threadCount);

	Utility::Texture RenderScene(const Entity::Scene& scene, const Entity::Camera& camera, size_t scatterDepth=50) const;

private:
	Tool::Vector2u m_OutputSize;
	size_t m_SampleCount;
	size_t m_ThreadCount;

};

} // namespace Gfx

#endif // GFX__RENDERER
