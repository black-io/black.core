#pragma once


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
	template< typename THost >
	inline InterconnectionSlot<THost>::InterconnectionSlot( const InterconnectionSlot& other )
		: BasicInterconnectionSlot{ other }
	{
	}

	template< typename THost >
	inline InterconnectionSlot<THost>::InterconnectionSlot( InterconnectionSlot&& other ) noexcept
		: BasicInterconnectionSlot{ std::forward<BasicInterconnectionSlot&&>( other ) }
	{
		other.Invalidate();
	}

	template< typename THost >
	inline InterconnectionSlot<THost>::InterconnectionSlot( const THost& host )
	{
		Interconnect( host );
	}

	template< typename THost >
	inline InterconnectionSlot<THost>::~InterconnectionSlot() noexcept
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
}
