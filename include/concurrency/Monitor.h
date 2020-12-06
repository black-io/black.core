#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	/**
		@brief	Representation of monitor mutex object.
		Monitor represents complex locking functionality. First of all, Monitor is a critical section so it may be just locked and unlocked as well.
		While been locked, monitor offers additional functions: monitor may block current thread execution and wait for signal from other thread.
		Notification may be done without locking monitor.
	*/
	class Monitor final : public Mutex
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

		/**
			@brief	Initiate waiting of signal for current thread if `condition` not return success result.
			This method initiates direct waiting only if `condition` returns `false`.
			While waiting, mutex of this monitor will be released, so any other thread would be able to lock it.
			After waiting, mutex of this monitor will be locked again by this thread, preventing any ambiguous situations between threads.
			@warning	Monitor must not be locked before calling this function! Locking is done internally.
			@param	condition						Callable conditions with calling signature like `void (*)()`. Other types will cause compiler errors.
			@tparam	TWaitCondition					Type of condition.
			@return									Returns reason why `Wait` was finished.
			@retval	MonitorWaitResult::Notified		Returned if monitor was notified.
			@retval	MonitorWaitResult::Condition	Returned if `condition` returns success result.
		*/
		template< typename TWaitCondition >
		inline const MonitorWaitResult Wait( TWaitCondition&& condition ) const;

		/**
			@brief	Initiate waiting of signal for current thread.
			Causes unconditional waiting until monitor notified.
			While waiting, mutex of this monitor will be released, so any other thread would be able to lock it.
			After waiting, mutex of this monitor will be locked again by this thread, preventing any ambiguous situations between threads.
			@warning	Monitor must not be locked before calling this function! Locking is done internally.
			@return									Returns reason why `Wait` was finished.
			@retval	MonitorWaitResult::Notified		Returned if monitor was notified.
		*/
		inline const MonitorWaitResult Wait() const;

		/**
			@brief	Initiate waiting of signal for current thread.
			Causes unconditional waiting until monitor notified. Waiting will be interrupted after `seconds` timeout.
			While waiting, mutex of this monitor will be released, so any other thread would be able to lock it.
			After waiting, mutex of this monitor will be locked again by this thread, preventing any ambiguous situations between threads.
			@warning	Monitor must not be locked before calling this function! Locking is done internally.
			@return									Returns reason why `Wait` was finished.
			@retval	MonitorWaitResult::Notified		Returned if monitor was notified.
			@retval	MonitorWaitResult::Timeout		Returned if timeout was reached.
		*/
		inline const MonitorWaitResult Wait( const Time seconds ) const;

		/**
			@brief	Notifies monitor, what cause one of waiting threads wake up.
			@note	Monitor may be locked in a purpose of data synchronization with waiting threads.
		*/
		inline void Notify() const		{ m_waiting_queue.notify_one(); };

		/**
			@brief	Notifies monitor, what cause all of waiting threads wake up.
			@note	Monitor may be locked in a purpose of data synchronization with waiting threads.
		*/
		inline void NotifyAll() const	{ m_waiting_queue.notify_all(); };

	private:
		mutable std::condition_variable_any	m_waiting_queue;	// Queue of waiting objects.
		mutable std::recursive_mutex		m_mutex;			// Mutex object.
	};
}
}
}
