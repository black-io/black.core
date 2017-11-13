#pragma once


namespace Black
{
inline namespace Core
{
	// Underlying enumeration type.
	template< typename TEnumeration >
	using UnderlyingType = typename std::underlying_type<TEnumeration>::type;
}
}
