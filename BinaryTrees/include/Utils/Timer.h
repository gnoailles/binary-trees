#pragma once
#include <chrono>

namespace Utils
{
	class Timer
	{
	public:
		using clock = std::chrono::high_resolution_clock;
		using nano = std::chrono::duration<double, std::nano>;
		using ms = std::chrono::duration<double, std::milli>;
		using sec = std::chrono::duration<double>;

	private:
		clock::time_point m_start;


	public:
		Timer();
		template<typename T = ms> T Elapsed() const
		{

			return clock::now() - m_start;
		}
		clock::time_point Restart();
		~Timer();
	};
}
