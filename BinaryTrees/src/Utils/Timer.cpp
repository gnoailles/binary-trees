#include <Utils/Timer.h>

using namespace Utils;

Timer::Timer() : m_start(clock::now())
{
	static_assert(std::chrono::steady_clock::is_steady, "Serious OS/C++ library issues. Steady clock is not steady");
}


Timer::clock::time_point Timer::Restart()
{
	m_start = clock::now();
	return m_start;
}

Timer::~Timer()
{
}
