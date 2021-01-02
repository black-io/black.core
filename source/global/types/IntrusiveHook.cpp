#include <black/core.h>
#include <black/core/algorithms.h>


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	// Its nothing to do with other hook on copy construction.
	IntrusiveHook::IntrusiveHook( const IntrusiveHook& other )
	{}

	// Move construction only invalidates the other hook.
	IntrusiveHook::IntrusiveHook( IntrusiveHook&& other ) noexcept
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
	IntrusiveHook& IntrusiveHook::operator=( IntrusiveHook&& other ) noexcept
	{
		other.Invalidate();
		return *this;
	}

	void IntrusiveHook::AddIntrusiveLink( Black::NotNull<RegularIntrusiveLink*> link ) const
	{
		EXPECTS_DEBUG( !Black::IsItemPresent( m_liinks, link.Get() ) );
		Black::UniqueAdd( m_liinks, link.Get() );
	}

	void IntrusiveHook::RemoveIntrusiveLink( Black::NotNull<RegularIntrusiveLink*> link ) const
	{
		EXPECTS_DEBUG( Black::IsItemPresent( m_liinks, link.Get() ) );
		Black::RemoveItem( m_liinks, link.Get() );
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
}
