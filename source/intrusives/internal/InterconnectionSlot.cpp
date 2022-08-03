#include <black/core/intrusives.h>


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
namespace
{
	// Logging channel.
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/Interconnection/Slot";
}


	InterconnectionSlot::InterconnectionSlot( const InterconnectionSlot& other )
	{
		InsertNear( other );
	}

	InterconnectionSlot::InterconnectionSlot( InterconnectionSlot&& other ) noexcept
		: m_previous{ std::exchange( other.m_previous, nullptr ) }
		, m_next{ std::exchange( other.m_next, nullptr ) }
	{
		CRET( IsAttached() );

		if( m_previous != nullptr )
		{
			m_previous->m_next = this;
		}

		if( m_next != nullptr )
		{
			m_next->m_previous = this;
		}
	}

	InterconnectionSlot::~InterconnectionSlot()
	{
		Detach();
	}

	void InterconnectionSlot::InsertBefore( InterconnectionSlot& other )
	{
		m_previous	= std::exchange( other.m_previous, this );
		m_next		= &other;

		ENSURES_DEBUG( m_previous != nullptr );
		m_previous->m_next = this;
	}

	void InterconnectionSlot::InsertAfter( InterconnectionSlot& other )
	{
		m_previous	= &other;
		m_next		= std::exchange( other.m_next, this );

		ENSURES_DEBUG( m_next != nullptr );
		m_next->m_previous = this;
	}

	void InterconnectionSlot::InsertNear( const InterconnectionSlot& other )
	{
		CRET( !other.IsAttached() );

		if( other.IsBegin() )
		{
			InsertBefore( *other.m_next );
		}
		else
		{
			InsertAfter( *other.m_previous );
		}
	}

	void InterconnectionSlot::Reset()
	{
		m_previous	= nullptr;
		m_next		= nullptr;
	}

	void InterconnectionSlot::Detach()
	{
		m_previous->m_next	= m_next;
		m_next->m_previous	= m_previous;
		Reset();
	}
}
}
}
}
