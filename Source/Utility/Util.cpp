#include <Utility/Util.h>
#include <cstdio>
#include <utility>
#include <malloc.h>

#if OS_WINDOWS
	#include <Windows.h>
	#include <ShellApi.h>
#endif

namespace Utility {

std::string ReadLine()
{
	std::string line;
	line.reserve(1u);

	while(true)
	{
		char c;
		std::fread(&c, sizeof(char), 1, stdin);
		if(c == '\n')
		{
			break;
		}

		line += c;
	}

	return line;
}

void FixEndianness(void* value, size_t size)
{
	// Machine byte order flag. Check with a lambda function and save on static const
	static const bool IsLittleEndianMachine = ([]() -> bool 
	{
		int x = 1;

		// If the machine is little-endian, the least important bit
		// will be on lower address. Little-endian will set the x=1
		// as 01000000, big-endian 00000001. So casting to char will
		// result in '1' for little-endian and '0' for big-endian.
		if(*((char*)&x) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	})();

	if(IsLittleEndianMachine)
	{
		return;
	}

	size_t i = 0;
	size_t j = size - 1u;
	while(i < j)
	{
		std::swap(static_cast<char*>(value)[i], static_cast<char*>(value)[j]);

		++i;
		--j;
	}
}

std::string GetBinaryNumber(const void* value, size_t size)
{
	// Fix endian
	void* fixedValue = alloca(size);
	for( size_t i=0 ; i<size ; ++i )
	{
		static_cast<char*>(fixedValue)[i] = static_cast<const char*>(value)[i];
	}
	Utility::FixEndianness(fixedValue, size);

	std::string numberAsStr;
	for( size_t i=0 ; i<size ; ++i )
	{
		numberAsStr += static_cast<char*>(fixedValue)[i];
	}
	return numberAsStr;
}

void RunExternalProgram(const std::string& programPath, const std::string& argv, bool async)
{
#if OS_WINDOWS
	auto hProcess = ShellExecuteA(GetDesktopWindow(), "open", programPath.c_str(), argv.c_str(), NULL, SW_SHOW);

	if(async == false)
	{
		auto status = STILL_ACTIVE;
		while(status == STILL_ACTIVE)
		{
			Sleep(100);
			auto result = GetExitCodeProcess(hProcess, &status);
			if(result == FALSE)
			{
				status = !STILL_ACTIVE;
			}
		}
	}
#else
	#error No implementation on this OS
#endif
}

} // namespace Utility
