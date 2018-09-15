#ifndef UTILITY__UTIL
#define UTILITY__UTIL

#include <string>

#if defined(_WIN32) || defined(WIN32)
	#define OS_WINDOWS 1
#else
	#error Unknown operating system
#endif

namespace Utility {

std::string ReadLine();

template<typename T> inline void FixEndianness(T& value);
void FixEndianness(void* value, size_t size);

template<typename T> inline std::string GetBinaryNumber(const T& value);
std::string GetBinaryNumber(const void* value, size_t size);

void RunExternalProgram(const std::string& programPath, const std::string& argv="", bool async=true);

/***** Implementations *****/

template<typename T> inline void FixEndianness(T& value)
{
	FixEndianness(&value, sizeof(T));
}
template<typename T> inline std::string GetBinaryNumber(const T& value)
{
	return GetBinaryNumber(&value, sizeof(T));
}

} // namespace Utility

#endif // UTILITY__UTIL
