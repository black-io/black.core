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
	/**
		@brief	Interconnection slot with true functionality.

		It manages the connection to `THost` and receives the calls of `Invalidate` function.
	*/
	template< typename THost >
	class InterconnectionSlot : protected BasicInterconnectionSlot
	{
	// Lifetime management.
	public:
		inline InterconnectionSlot() = default;

		inline InterconnectionSlot( const InterconnectionSlot& other );
		inline InterconnectionSlot( InterconnectionSlot&& other ) noexcept;

		explicit inline InterconnectionSlot( const THost& host );

	// Heirs lifetime management.
	protected:
		inline ~InterconnectionSlot() noexcept;

	// Heirs compatible interface.
	protected:
		// Perform the interconnection.
		inline void Interconnect( const THost& host );

		// Perform the disconnection from interconnection.
		inline void Disconnect();
	};
}
}
}
}
}
