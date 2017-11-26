#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	/**
		@brief	Representation of critical section.
		Critical section object ensures that only one thread can lock it in same time, other threads will be blocked and enqueued for locking.
	*/
	class CriticalSection final : public Mutex
	{
	public:
		/**
			@see	Mutex::Lock()
		*/
		virtual void Lock() const override		{ m_mutex.lock(); };

		/**
			@see	Mutex::Unlock()
		*/
		virtual void Unlock() const override	{ m_mutex.unlock(); };

	private:
		mutable std::recursive_mutex	m_mutex;	// Mutex object.
	};
}
}
}
