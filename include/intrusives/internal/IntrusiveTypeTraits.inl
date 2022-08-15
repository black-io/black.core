#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	template< typename TValue, typename TSlot, TSlot TValue::* SLOT_POINTER >
	inline TValue& IntrusiveTypeTraits<TValue, SLOT_POINTER>::GetValue( TSlot& slot )
	{
		return *reinterpret_cast<TValue*>( reinterpret_cast<std::byte*>( &slot ) - SLOT_OFFSET );
	}

	template< typename TValue, typename TSlot, TSlot TValue::* SLOT_POINTER >
	inline const TValue& IntrusiveTypeTraits<TValue, SLOT_POINTER>::GetValue( const TSlot& slot )
	{
		return *reinterpret_cast<const TValue*>( reinterpret_cast<const std::byte*>( &slot ) - SLOT_OFFSET );
	}

	template< typename TValue, typename TSlot, TSlot TValue::* SLOT_POINTER >
	inline TSlot& IntrusiveTypeTraits<TValue, SLOT_POINTER>::GetSlot( TValue& value )
	{
		return value.*SLOT_POINTER;
	}

	template< typename TValue, typename TSlot, TSlot TValue::* SLOT_POINTER >
	inline const TSlot& IntrusiveTypeTraits<TValue, SLOT_POINTER>::GetSlot( const TValue& value )
	{
		return value.*SLOT_POINTER;
	}

	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* SLOT_POINTER >
	inline TValue& IntrusiveTypeTraits<TValue, SLOT_POINTER>::GetValue( TSlot& slot )
	{
		static_assert( std::is_base_of_v<TStorage, TValue>, "Type of value should be derived from type of storage." );
		return static_cast<TValue&>( StorageTraits::GetValue( slot ) );
	}

	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* SLOT_POINTER >
	inline const TValue& IntrusiveTypeTraits<TValue, SLOT_POINTER>::GetValue( const TSlot& slot )
	{
		static_assert( std::is_base_of_v<TStorage, TValue>, "Type of value should be derived from type of storage." );
		return static_cast<const TValue&>( StorageTraits::GetValue( slot ) );
	}

	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* SLOT_POINTER >
	inline TSlot& IntrusiveTypeTraits<TValue, SLOT_POINTER>::GetSlot( TValue& value )
	{
		static_assert( std::is_base_of_v<TStorage, TValue>, "Type of value should be derived from type of storage." );
		return StorageTraits::GetSlot( static_cast<TStorage&>( value ) );
	}

	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* SLOT_POINTER >
	inline const TSlot& IntrusiveTypeTraits<TValue, SLOT_POINTER>::GetSlot( const TValue& value )
	{
		static_assert( std::is_base_of_v<TStorage, TValue>, "Type of value should be derived from type of storage." );
		return StorageTraits::GetSlot( static_cast<const TStorage&>( value ) );
	}
}
}
}
}
