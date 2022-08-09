#include <black/core/intrusives.h>


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
inline namespace Interconnection
{
namespace
{
	// Logging channel.
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/Interconnection/Slot";
}


	BasicInterconnectionSlot::BasicInterconnectionSlot( const BasicInterconnectionSlot& other )
	{
		CRET( !other.IsAttached() );

		if( other.IsBegin() )
		{
			m_next		= other.m_next;
			m_previous	= m_next->m_previous;
		}
		else
		{
			m_previous	= other.m_previous;
			m_next		= m_previous->m_next;
		}

		m_next->m_previous	= this;
		m_previous->m_next	= this;
	}

	BasicInterconnectionSlot::BasicInterconnectionSlot( BasicInterconnectionSlot&& other ) noexcept
		: BasicInterconnectionSlot{ std::exchange( other.m_previous, nullptr ), std::exchange( other.m_next, nullptr ) }
	{
		if( m_previous != nullptr )
		{
			m_previous->m_next = this;
		}

		if( m_next != nullptr )
		{
			m_next->m_previous = this;
		}
	}

	BasicInterconnectionSlot::~BasicInterconnectionSlot() noexcept
	{
		Detach();
	}

	void BasicInterconnectionSlot::AttachTo( const Black::Interconnection& interconnection )
	{
		interconnection.RegisterSlot( *this );
	}

	void BasicInterconnectionSlot::Detach()
	{
		CRET( !IsAttached() );

		BasicInterconnectionSlot* const previous	= std::exchange( m_previous, nullptr );
		BasicInterconnectionSlot* const next		= std::exchange( m_next, nullptr );

		if( previous != nullptr )
		{
			previous->m_next = next;
		}

		if( next != nullptr )
		{
			next->m_previous = previous;
		}
	}

	BasicInterconnectionSlot::BasicInterconnectionSlot( BasicInterconnectionSlot* previous, BasicInterconnectionSlot* next )
		: m_previous{ previous }
		, m_next{ next }
	{
	}

	void BasicInterconnectionSlot::InsertBefore( BasicInterconnectionSlot& other )
	{
		EXPECTS_DEBUG( other.IsAttached() );
		EXPECTS_DEBUG( !other.IsBegin() );
		m_previous	= std::exchange( other.m_previous, this );
		m_next		= std::exchange( m_previous->m_next, this );
	}

	void BasicInterconnectionSlot::Reset()
	{
		m_previous	= nullptr;
		m_next		= nullptr;
	}
}
}
}
}
}
