#pragma once


namespace Black
{
inline namespace Core
{
inline namespace TypeTraits
{
	// Underlying enumeration type.
	template< typename TEnumeration >
	using UnderlyingType = typename std::underlying_type<TEnumeration>::type;

	// Conditional type.
	template< bool CONDITION, typename TTrueType, typename TFalseType >
	using Conditional = typename std::conditional<CONDITION, TTrueType, TFalseType>::type;

	// Conditional type switch.
	template< bool CONDITION, typename TTrueType = void >
	using EnableIf = typename std::enable_if<CONDITION, TTrueType>::type;

	// Remove the `const` type qualifier.
	template< typename TConstType >
	using RemoveConst = typename std::remove_const<TConstType>::type;

	// Decay the type.
	template< typename TDecoratedType >
	using Decay = typename std::decay<TDecoratedType>::type;
}
}
}
