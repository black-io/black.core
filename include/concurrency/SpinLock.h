#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	/**
		@brief		Spin-lock object.
		Spin locks are synchronization primitives, like mutex or semaphore. But, spin-locks uses active blocking pattern instead.
		@warning	Spin-lock uses active blocking, so it's strongly recommended to not use it for guarding time-consumable operations.
		@note		Spin-locks most useful for guarding of low-complexity operations.
	*/
	class SpinLock final : public Mutex
	{
	public:
		// @see	Mutex::Lock()
		virtual inline void Lock() const override;

		// @see	Mutex::Unlock()
		virtual inline void Unlock() const override;

	private:
		// Latching the lock.
		inline void AcquireLock() const;

		// Unlatching and reset the lock.
		inline void ReleaseLock() const;

	private:
		mutable std::atomic_flag	m_latch			= ATOMIC_FLAG_INIT;	// Latch for spins.
		mutable std::thread::id		m_lock_owner;						// Thread that latched the lock.
		mutable volatile int32_t	m_locks_count	= 0;				// In order of recursive locks.
	};
}
}
}
