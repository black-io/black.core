#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	/// Get the number of elapsed seconds.
	Time GetCurrentTime();

	// Suspend the thread for a given duration.
	void SleepCurrentThread( TimeDuration duration );

	// Instruct the platform to end the scheduled time quantum for current thread.
	void YieldCurrentThread();

	/**
		@brief	Get the number of concurrent threads supported by system.
		The value returned may be the number of CPU hardware cores.
		@note	This value can be only considered as hint.
		@return	Number of supported concurrent threads.
	*/
	const size_t GetHardwareThreadsCount();
}
}
}
