#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	template< typename TValue, auto MEMBER_POINTER >
	class IntrusiveTypeTraits;

	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	class IntrusiveTypeTraits<TValue, MEMBER_POINTER> final
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

	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* MEMBER_POINTER >
	class IntrusiveTypeTraits<TValue, MEMBER_POINTER> final
	{
	// Public interface.
	public:
		// Get the value by given slot.
		static inline TValue& GetValue( TSlot& slot );

		// Get the value by given slot.
		static inline const TValue& GetValue( const TSlot& slot );

		// Get the slot by given value.
		static inline TSlot& GetSlot( TValue& value );

		// Get the slot by given value.
		static inline const TSlot& GetSlot( const TValue& value );

	// Private inner types.
	private:
		// Type traits for storage type.
		using StorageTraits = IntrusiveTypeTraits<TStorage, MEMBER_POINTER>;
	};

	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	using IntrusiveTraits = IntrusiveTypeTraits<TValue, MEMBER_POINTER>;
}
}
}
}
