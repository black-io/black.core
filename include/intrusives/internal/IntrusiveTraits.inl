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
	inline TValue& IntrusiveTraits<TValue, TSlot, MEMBER_POINTER>::GetValue( TSlot& slot )
	{
		return *reinterpret_cast<TValue*>( reinterpret_cast<std::byte*>( &slot ) - MEMBER_OFFSET );
	}

	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	inline const TValue& IntrusiveTraits<TValue, TSlot, MEMBER_POINTER>::GetValue( const TSlot& slot )
	{
		return *reinterpret_cast<const TValue*>( reinterpret_cast<const std::byte*>( &slot ) - MEMBER_OFFSET );
	}

	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	inline TSlot& IntrusiveTraits<TValue, TSlot, MEMBER_POINTER>::GetSlot( TValue& value )
	{
		return value.*MEMBER_POINTER;
	}

	template< typename TValue, typename TSlot, TSlot TValue::* MEMBER_POINTER >
	inline const TSlot& IntrusiveTraits<TValue, TSlot, MEMBER_POINTER>::GetSlot( const TValue& value )
	{
		return value.*MEMBER_POINTER;
	}
}
}
}
}
