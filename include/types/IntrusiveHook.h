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

	// Public interface.
	public:
		// Cares about proper invalidation of hook.
		virtual ~IntrusiveHook();


		// Add the link into hook.
		// This is a service function, it may be used only by intrusive link.
		void AddIntrusiveLink( Black::NotNull<RegularIntrusiveLink> link );

		// Remove the link form hook.
		// This is a service function, it may be used only by intrusive link.
		void RemoveIntrusiveLink( Black::NotNull<RegularIntrusiveLink> link );

	// Construction interface.
	protected:
		IntrusiveHook() = default;
		IntrusiveHook( const IntrusiveHook& other );
		IntrusiveHook( IntrusiveHook&& other );

		IntrusiveHook& operator = ( const IntrusiveHook& other );
		IntrusiveHook& operator = ( IntrusiveHook&& other );

	private:
		// Invalidate the hook.
		void Invalidate();

	private:
		std::deque<RegularIntrusiveLink*>	m_liinks;	// Connected links.
	};
}
}
}