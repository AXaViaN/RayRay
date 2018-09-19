#ifndef ENTITY__RENDERER
#define ENTITY__RENDERER

#include <Entity/Camera.h>
#include <Entity/Scene.h>
#include <Tool/Texture.h>

namespace Entity {

class Renderer
{
public:
	Renderer(const Utility::Vector2u& outputSize, size_t aaSampleCount);

	Tool::Texture RenderScene(const Entity::Scene& scene, const Entity::Camera& camera) const;

private:
	Utility::Vector2u m_OutputSize;
	size_t m_AASampleCount;

};

} // namespace Entity

#endif // ENTITY__RENDERER
