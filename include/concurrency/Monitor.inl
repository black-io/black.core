#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	template< typename TWaitCondition >
	inline const MonitorWaitResult Monitor::Wait( TWaitCondition&& condition ) const
	{
		auto lock = std::unique_lock<std::recursive_mutex>( m_mutex );
		m_waiting_queue.wait( lock, std::forward<TWaitCondition>( condition ) );
		return MonitorWaitResult::Notified;
	}

	inline const MonitorWaitResult Monitor::Wait() const
	{
		auto lock = std::unique_lock<std::recursive_mutex>( m_mutex );
		m_waiting_queue.wait( lock );
		return MonitorWaitResult::Notified;
	}

	inline const MonitorWaitResult Monitor::Wait( const Time seconds ) const
	{
		auto lock		= std::unique_lock<std::recursive_mutex>( m_mutex );
		auto timeout	= Black::GetDurationFromSeconds( seconds );
		auto status		= m_waiting_queue.wait_for( lock, timeout );
		return ( status == std::cv_status::timeout )? MonitorWaitResult::Timeout : MonitorWaitResult::Notified;
	}
}
}
}
