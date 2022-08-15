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
		@brief	Type traits for intrusive containers.

		This traits used by intrusive containers operate with element slots and elements.
		Traits allow containers to store the values of one type and operate with container slot from the base type of one.

		@tparam	TValue			Type of value stored by container.
		@tparam	SLOT_POINTER	Pointer to class member with type of container slot.
	*/
	template< typename TValue, auto SLOT_POINTER >
	class IntrusiveTypeTraits;

	/**
		@brief	Type traits for case the container slot is stored by the container value type.

		@tparam	TValue			Type of value stored by container.
		@tparam	TSlot			Type of slot for container.
		@tparam	SLOT_POINTER	Pointer to class member with type of container slot.
	*/
	template< typename TValue, typename TSlot, TSlot TValue::* SLOT_POINTER >
	class IntrusiveTypeTraits<TValue, SLOT_POINTER> final
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
		static inline const ptrdiff_t SLOT_OFFSET = ptrdiff_t( &( ((TValue*)nullptr)->*SLOT_POINTER ) );
	};

	/**
		@brief	Type traits for case the container slot is stored by the base type of container value.

		@tparam	TValue			Type of value stored by container.
		@tparam	TStorage		Type of container slot storage, that should be the base type for value type.
		@tparam	TSlot			Type of slot for container.
		@tparam	SLOT_POINTER	Pointer to class member with type of container slot.
	*/
	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* SLOT_POINTER >
	class IntrusiveTypeTraits<TValue, SLOT_POINTER> final
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
		using StorageTraits = IntrusiveTypeTraits<TStorage, SLOT_POINTER>;
	};
}
}
}
}
