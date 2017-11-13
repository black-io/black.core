#pragma once


namespace Black
{
inline namespace Core
{
	// Enumeration type check.
	template< typename TCondition >
	constexpr bool IS_ENUMERATION = std::is_enum<TCondition>::value;
}
}
