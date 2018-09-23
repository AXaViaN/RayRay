#ifndef UTILITY__SCATTER_RESULT
#define UTILITY__SCATTER_RESULT

#include <Tool/Ray.h>
#include <Utility/Color.h>

namespace Utility {

struct ScatterResult
{
	Tool::Ray ScatterRay;
	Utility::Color ObjectColor;

	bool IsScatter = false;

public:
	inline ScatterResult();
};

inline ScatterResult::ScatterResult() : 
	ScatterRay({}, {})
{
}

} // namespace Utility

#endif // UTILITY__SCATTER_RESULT
