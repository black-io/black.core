#include <black.core.h>


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	Time GetCurrentTime()
	{
		return GetSecondsFromDuration( std::chrono::high_resolution_clock::now().time_since_epoch() );
	}

	void SleepCurrentThread( TimeDuration duration )
	{
		std::this_thread::sleep_for( duration );
	}

	void YieldCurrentThread()
	{
		std::this_thread::yield();
	}

	const size_t GetHardwareThreadsCount()
	{
		return std::thread::hardware_concurrency();
	}
}
}
}
