#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
		@brief	Intrusive hook specification.

		@note	`IntrusiveHook` is not thread safe. So, it must be used carefully in concurrent code.
	*/
	class IntrusiveHook
	{
	// Inner entities.
	public:
		// Regular intrusive link.
		class RegularIntrusiveLink
		{
			friend class IntrusiveHook;
		public:
			// Used by intrusive hook to invalidate the link.
			virtual void InvalidateIntrusiveLink() = 0;
		};

	private:
	};
}
}
}
