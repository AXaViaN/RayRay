#ifndef ASSET__MATERIAL
#define ASSET__MATERIAL

namespace Tool {
	class Ray;
	class HitResult;
	class ScatterResult;
}

namespace Asset {

class Material
{
public:
	virtual Tool::ScatterResult ScatterCheck(const Tool::Ray& ray, const Tool::HitResult& hitResult) const = 0;

};

} // namespace Asset

#endif // ASSET__MATERIAL
