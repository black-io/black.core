#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	template< typename THost >
	inline InterconnectionSlot<THost>::InterconnectionSlot( const InterconnectionSlot& other )
		: BasicInterconnectionSlot{ other }
	{
	}

	template< typename THost >
	inline InterconnectionSlot<THost>::InterconnectionSlot( InterconnectionSlot&& other )
		: BasicInterconnectionSlot{ std::move( static_cast<BasicInterconnectionSlot&>( other ) ) }
	{
		other.Invalidate();
	}

	template< typename THost >
	inline InterconnectionSlot<THost>::~InterconnectionSlot()
	{
		Detach();
	}

	template< typename THost >
	inline InterconnectionSlot<THost>::InterconnectionSlot( const THost& host )
	{
		AttachTo( host );
	}

	template< typename THost >
	inline void InterconnectionSlot<THost>::Interconnect( const THost& host )
	{
		Detach();
		AttachTo( host );
	}
}
}
}
}
