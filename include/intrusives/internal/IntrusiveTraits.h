#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	/**
		@brief	Intrusive container traits.
	*/
	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	class IntrusiveTraits final
	{
	// Public static interface.
	public:
		// Get the value by given slot.
		static inline TValue& GetValue( TSlot& slot );

		// Get the value by given slot.
		static inline const TValue& GetValue( const TSlot& slot );

		// Get the slot by given value.
		static inline TSlot& GetSlot( TValue& value );

		// Get the slot by given value.
		static inline const TSlot& GetSlot( const TValue& value );

	// Private constants.
	private:
		// Byte offset from object base address to slot member.
		static inline const ptrdiff_t MEMBER_OFFSET = ptrdiff_t( &( ((TValue*)nullptr)->*MEMBER_POINTER ) );
	};
}
}
}
}
