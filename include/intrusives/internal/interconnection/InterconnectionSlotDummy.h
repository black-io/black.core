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
		@brief	Interconnection slot with dummy functionality.

		All the functionality of interconnection slot is just emulated.
		This slot does not manage the interconnection and does not receive the calls of `Invalidate` function.
	*/
	template< typename THost >
	class InterconnectionSlotDummy
	{
	// Lifetime management.
	public:
		inline InterconnectionSlotDummy()										= default;
		inline InterconnectionSlotDummy( const InterconnectionSlotDummy& )		= default;
		inline InterconnectionSlotDummy( InterconnectionSlotDummy&& ) noexcept	= default;

		explicit inline InterconnectionSlotDummy( const THost& )				{};

	// Heirs lifetime management.
	protected:
		inline ~InterconnectionSlotDummy() = default;

	// Heirs compatible interface.
	protected:
		// Empty stub for functional symmetry.
		inline void Interconnect( const THost& )	{};

	// Heirs compatible virtual interface.
	protected:
		// Empty stub for functional symmetry.
		virtual inline void Invalidate() = 0;
	};
}
}
}
}
}
