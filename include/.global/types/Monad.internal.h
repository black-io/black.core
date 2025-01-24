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
	// Common deduction path. The inner type is regular monad.
	template< typename TResult >
	struct MonadSelector final
	{
		using Type = Monad<TResult>;
	};

	// Terminal path of deduction. The inner type is void.
	template<>
	struct MonadSelector<void> final
	{
		using Type = void;
	};

	// Type selector. Represents the regular monad or void type.
	template< typename TFunction, typename TValue >
	using MonadOrVoid = typename MonadSelector<std::invoke_result_t<TFunction, TValue>>::Type;
}
}
}
}
}
