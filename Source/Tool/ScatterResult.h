#ifndef TOOL__SCATTER_RESULT
#define TOOL__SCATTER_RESULT

#include <Tool/Ray.h>
#include <Tool/Color.h>

namespace Tool {

class ScatterResult
{
public:
	inline ScatterResult();

public:
	Tool::Ray ScatterRay;
	Tool::Color ObjectColor;

	bool IsScatter = false;

};

/***** IMPLEMENTATION *****/

inline ScatterResult::ScatterResult() : 
	ScatterRay({}, {})
{
}

} // namespace Tool

#endif // TOOL__SCATTER_RESULT
