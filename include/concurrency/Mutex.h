#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Concurrency
{
	/**
		@brief	Abstract mutex representation.
		Such mutex can be locked in one thread, what prevents locking it in another threads and block that threads.
		Mutex is an object with unique state, so no copy construction allowed for it and copy assignment as well.
		Constructor and destructor are hidden from public access to prevent such manipulations on objects of derived classes.
	*/
	class Mutex : private Black::NonCopyable
	{
	public:
		/**
			@brief	Initiate mutex lock.
			If some thread locks mutex, all other threads will be blocked in execution when try lock it too.
		*/
		virtual void Lock() const	= 0;

		/**
			@brief	Ends mutex lock.
			After that mutex becomes free and may be blocked by any another thread.
		*/
		virtual void Unlock() const	= 0;

	protected:
		Mutex()				= default;
		virtual ~Mutex()	= default;
	};
}
}
}
