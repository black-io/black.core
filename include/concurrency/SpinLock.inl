#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	inline void SpinLock::Lock() const
	{
		AcquireLock();
		++m_locks_count;
	}

	inline void SpinLock::Unlock() const
	{
		const auto this_thread_id = std::this_thread::get_id();
		// Prevent abnormal usage of spin-lock.
		CRET( m_lock_owner != this_thread_id );
		CRET( m_locks_count < 1 );

		--m_locks_count;
		ReleaseLock();
	}

	inline void SpinLock::AcquireLock() const
	{
		const auto this_thread_id = std::this_thread::get_id();
		CRET( m_lock_owner == this_thread_id );

		while( m_latch.test_and_set( std::memory_order::memory_order_acquire ) );

		m_lock_owner	= this_thread_id;
		m_locks_count	= 0;
	}

	inline void SpinLock::ReleaseLock() const
	{
		CRET( m_locks_count > 0 );
		m_lock_owner	= std::thread::id();
		m_locks_count	= 0;
		m_latch.clear( std::memory_order::memory_order_release );
	}
}
}
}
