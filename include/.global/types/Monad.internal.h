#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
namespace Internal
{
	// Common deduction path. The inner type is regular Hypothetical.
	template< typename TResult >
	struct HypotheticalSelector final
	{
		using Type = Hypothetical<TResult>;
	};

	// Terminal path of deduction. The inner type is void.
	template<>
	struct HypotheticalSelector<void> final
	{
		using Type = void;
	};

	// Type selector. Represents the regular Hypothetical or void type.
	template< typename TFunction, typename TValue >
	using HypotheticalOrVoid = typename HypotheticalSelector<std::invoke_result_t<TFunction, TValue>>::Type;

	template< typename TValue >
	using HypotheticalForwardingValue = std::conditional_t<std::is_lvalue_reference_v<TValue>, TValue&, TValue&&>;
}
}
}
}
}
