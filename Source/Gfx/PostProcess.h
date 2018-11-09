#ifndef GFX__POST_PROCESS
#define GFX__POST_PROCESS

#include <Tool/Color.h>
#include <Utility/Texture.h>
#include <functional>

namespace Gfx {

class PostProcess
{
public:
	static Utility::Texture Process(const Utility::Texture& input, 
									const std::function< Tool::Color(const Tool::Color& color, const Tool::Vector2u& coord) >& pixelShader);

	static Utility::Texture GetLuminance(const Utility::Texture& input);
	static Utility::Texture GaussianBlur(const Utility::Texture& input, size_t size);
	static Utility::Texture Bloom(const Utility::Texture& input, const Utility::Texture& highlight);
	static Utility::Texture HDRToneMap(const Utility::Texture& input, float exposure);
	static Utility::Texture GammaCorrection(const Utility::Texture& input, float gamma);

};

} // namespace Gfx

#endif // GFX__POST_PROCESS
