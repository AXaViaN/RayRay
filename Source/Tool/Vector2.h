#ifndef TOOL__VECTOR2
#define TOOL__VECTOR2

namespace Tool {

template<typename T> class Vector2;
using Vector2f = Vector2<float>;
using Vector2u = Vector2<unsigned int>;

template<typename T> class Vector2
{
public:
	T X = 0;
	T Y = 0;

};

} // namespace Tool

#endif // TOOL__VECTOR2
