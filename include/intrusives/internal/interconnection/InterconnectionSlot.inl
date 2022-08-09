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
	inline InterconnectionSlot<THost>::InterconnectionSlot( const THost& host )
	{
		Interconnect( host );
	}

	template< typename THost >
	inline InterconnectionSlot<THost>::~InterconnectionSlot()
	{
		Disconnect();
	}

	template< typename THost >
	inline void InterconnectionSlot<THost>::Interconnect( const THost& host )
	{
		Disconnect();
		AttachTo( host );
	}

	template< typename THost >
	inline void InterconnectionSlot<THost>::Disconnect()
	{
		Detach();
	}
}
}
}
}
