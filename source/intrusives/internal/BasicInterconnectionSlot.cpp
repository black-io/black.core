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

	InterconnectionSlot::InterconnectionSlot( InterconnectionSlot&& other ) noexcept
		: InterconnectionSlot{ std::exchange( other.m_previous, nullptr ), std::exchange( other.m_next, nullptr ) }
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

	InterconnectionSlot::~InterconnectionSlot() noexcept
	{
		Detach();
	}

	void InterconnectionSlot::RegisterAt( Black::Interconnection& interconnection )
	{
		interconnection.RegisterSlot( *this );
	}

	InterconnectionSlot::InterconnectionSlot( InterconnectionSlot* previous, InterconnectionSlot* next )
		: m_previous{ previous }
		, m_next{ next }
	{
	}

	void InterconnectionSlot::InsertBefore( InterconnectionSlot& other )
	{
		EXPECTS_DEBUG( other.IsAttached() );
	}

	void InterconnectionSlot::Reset()
	{
		m_previous	= nullptr;
		m_next		= nullptr;
	}

	void InterconnectionSlot::Detach()
	{
		CRET( !IsAttached() );

		InterconnectionSlot* const previous	= std::exchange( m_previous, nullptr );
		InterconnectionSlot* const next		= std::exchange( m_next, nullptr );

		if( previous != nullptr )
		{
			previous->m_next = next;
		}

		if( next != nullptr )
		{
			next->m_previous = previous;
		}
	}
}
}
}
}
