#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	/**
		@brief	Representation of mutex locking algorithm.
		Object of `MutexLock` will lock mutex on constructor and unlock it when destructed.
		Mutex lock is an object with unique state. It's impossible to copy this object.
	*/
	class MutexLock final : private Black::NonTransferable
	{
	public:
		/**
			@brief	Forces `mutex` to be locked.
			`mutex` object will be held inside of this lock until lock destroyed.
		*/
		MutexLock( const Mutex& mutex ) : m_mutex{ mutex }	{ m_mutex.Lock(); };

		// Unlocks and frees previously held `mutex` object.
		~MutexLock()										{ m_mutex.Unlock(); };

	private:
		const Mutex&	m_mutex;	// Stored mutex object.
	};
}
}
}
