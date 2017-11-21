#include <black.core.h>


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	// Its nothing to do with other hook on copy construction.
	IntrusiveHook::IntrusiveHook( const IntrusiveHook& other )
	{}

	// Move construction only invalidates the other hook.
	IntrusiveHook::IntrusiveHook( IntrusiveHook&& other )
	{
		other.Invalidate();
	}

	IntrusiveHook::~IntrusiveHook()
	{
		Invalidate();
	}

	// Copy assignment is an empty function.
	IntrusiveHook& IntrusiveHook::operator=( const IntrusiveHook& other )
	{
		return *this;
	}

	// Move assignment invalidates the other hook.
	IntrusiveHook& IntrusiveHook::operator=( IntrusiveHook&& other )
	{
		other.Invalidate();
		return *this;
	}

	void IntrusiveHook::AddIntrusiveLink( Black::NotNull<RegularIntrusiveLink> link )
	{
		EXPECTS_DEBUG( !Black::IsItemExists( m_liinks, link.get() ) );
		Black::UniqueAdd( m_liinks, link.get() );
	}

	void IntrusiveHook::RemoveIntrusiveLink( Black::NotNull<RegularIntrusiveLink> link )
	{
		EXPECTS_DEBUG( Black::IsItemExists( m_liinks, link.get() ) );
		Black::RemoveItem( m_liinks, link.get() );
	}

	void IntrusiveHook::Invalidate()
	{
		CRET( m_liinks.empty() );
		for( auto link : m_liinks )
		{
			link->InvalidateIntrusiveLink();
		}

		m_liinks.clear();
	}
}
}
}
