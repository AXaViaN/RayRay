#ifndef UTILITY__VECTOR2
#define UTILITY__VECTOR2

namespace Utility {

template<typename T> class Vector2;
using Vector2f = Vector2<float>;
using Vector2u = Vector2<unsigned int>;

template<typename T> class Vector2
{
public:
	T X = 0;
	T Y = 0;

};

} // namespace Utility

#endif // UTILITY__VECTOR2
