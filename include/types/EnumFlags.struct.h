#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	// Marker type to mark the enumeration with ordinal values.
	template< typename TEnumeration >
	struct OrdinalEnumeration final
	{
		static_assert( std::is_enum_v<TEnumeration>, "`TEnumeration` have to be enumeration type." );
	};

	// Marker type to mark the enumeration with bit-mask values.
	template< typename TEnumeration >
	struct BitmaskEnumeration final
	{
		static_assert( std::is_enum_v<TEnumeration>, "`TEnumeration` have to be enumeration type." );
	};
}
}
}
