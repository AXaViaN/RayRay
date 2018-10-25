#ifndef TOOL__TIMER
#define TOOL__TIMER

#include <chrono>
#include <string>
#include <cstdio>

namespace Tool {

class Timer
{
public:
	inline Timer();
	inline virtual ~Timer() noexcept;

	inline void Restart();
	inline void Split();
	
	/*
	 *	Calls Split() and returns duration
	 */
	inline float GetSeconds();
	/*
	 *	Returns duration from the last Split() call
	 */
	inline float GetLastSeconds() const;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_End;

};

class ScopedTimer : private Timer
{
public:
	/*
	 *	Use %time as identifier. E.g. "Completed in %time sec."
	 */
	inline ScopedTimer(const std::string& printFormat);
	inline ScopedTimer(float* result);
	inline ~ScopedTimer() noexcept;

private:
	std::string m_PrintFormat;
	float* m_ResultPtr = nullptr;

};

/***** Timer IMPLEMENTATION *****/

inline Timer::Timer()
{
	Restart();
}
inline Timer::~Timer() noexcept
{
}

inline void Timer::Restart()
{
	m_Start = std::chrono::high_resolution_clock::now();
	m_End = m_Start;
}
inline void Timer::Split()
{
	m_End = std::chrono::high_resolution_clock::now();
}

inline float Timer::GetSeconds()
{
	Split();
	return GetLastSeconds();
}
inline float Timer::GetLastSeconds() const
{
	auto duration = std::chrono::duration<float>(m_End - m_Start);
	return duration.count();
}

/***** ScopedTimer IMPLEMENTATION *****/

inline ScopedTimer::ScopedTimer(const std::string& printMessage) : 
	m_PrintFormat(printMessage)
{
}
inline ScopedTimer::ScopedTimer(float* result) : 
	m_ResultPtr(result)
{
}
inline ScopedTimer::~ScopedTimer() noexcept
{
	auto result = this->Timer::GetSeconds();

	if(m_ResultPtr != nullptr)
	{
		*m_ResultPtr = result;
	}
	else
	{
		std::string identifier = "%time";
		auto identifierPos = m_PrintFormat.find(identifier);
		if(identifierPos != m_PrintFormat.npos)
		{
			m_PrintFormat.replace(identifierPos, identifier.size(), std::to_string(result));
		}

		std::printf(m_PrintFormat.c_str());
	}
}

} // namespace Tool

#endif // TOOL__TIMER
