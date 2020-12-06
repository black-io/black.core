#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	// Result of `Monitor::Wait` functions.
	enum class MonitorWaitResult : uint8_t
	{
		Exception = 0,	// Some exception was occurred while waiting.
		Notified,		// Monitor was notified.
		Timeout,		// Timeout was reached.
	};
}
}
}
