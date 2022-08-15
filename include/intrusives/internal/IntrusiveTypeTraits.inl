#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	inline TValue& IntrusiveTypeTraits<TValue, MEMBER_POINTER>::GetValue( TSlot& slot )
	{
		return *reinterpret_cast<TValue*>( reinterpret_cast<std::byte*>( &slot ) - MEMBER_OFFSET );
	}

	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	inline const TValue& IntrusiveTypeTraits<TValue, MEMBER_POINTER>::GetValue( const TSlot& slot )
	{
		return *reinterpret_cast<const TValue*>( reinterpret_cast<const std::byte*>( &slot ) - MEMBER_OFFSET );
	}

	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	inline TSlot& IntrusiveTypeTraits<TValue, MEMBER_POINTER>::GetSlot( TValue& value )
	{
		return value.*MEMBER_POINTER;
	}

	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	inline const TSlot& IntrusiveTypeTraits<TValue, MEMBER_POINTER>::GetSlot( const TValue& value )
	{
		return value.*MEMBER_POINTER;
	}

	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* MEMBER_POINTER >
	inline TValue& IntrusiveTypeTraits<TValue, MEMBER_POINTER>::GetValue( TSlot& slot )
	{
		static_assert( std::is_base_of_v<TStorage, TValue>, "Type of value should be derived from type of storage." );
		return static_cast<TValue&>( StorageTraits::GetValue( slot ) );
	}

	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* MEMBER_POINTER >
	inline const TValue& IntrusiveTypeTraits<TValue, MEMBER_POINTER>::GetValue( const TSlot& slot )
	{
		static_assert( std::is_base_of_v<TStorage, TValue>, "Type of value should be derived from type of storage." );
		return static_cast<const TValue&>( StorageTraits::GetValue( slot ) );
	}

	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* MEMBER_POINTER >
	inline TSlot& IntrusiveTypeTraits<TValue, MEMBER_POINTER>::GetSlot( TValue& value )
	{
		static_assert( std::is_base_of_v<TStorage, TValue>, "Type of value should be derived from type of storage." );
		return StorageTraits::GetSlot( static_cast<TStorage&>( value ) );
	}

	template< typename TValue, typename TStorage, typename TSlot, TSlot TStorage::* MEMBER_POINTER >
	inline const TSlot& IntrusiveTypeTraits<TValue, MEMBER_POINTER>::GetSlot( const TValue& value )
	{
		static_assert( std::is_base_of_v<TStorage, TValue>, "Type of value should be derived from type of storage." );
		return StorageTraits::GetSlot( static_cast<const TStorage&>( value ) );
	}
}
}
}
}
