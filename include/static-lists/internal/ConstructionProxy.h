#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	/**
		@brief	Construction proxy to properly construct the implementations of static list.

		Construction proxy implements the selectivity of object construction function between aggregate construction and narrowing construction.

		@tparam	TImplementation	The implementation type to create the objects.
	*/
	template< typename TImplementation >
	struct ConstructionProxy final
	{
		// Whether the `TImplementation` can be constructed through defined constructor with given argument types.
		template< typename... TArguments >
		static inline constexpr bool IS_CONSTRUCTIBLE = std::is_constructible_v<TImplementation, TArguments...>;

		// Narrowing construction, in case of `TImplementation` may be constructed.
		template< typename... TArguments >
		static inline std::enable_if_t<IS_CONSTRUCTIBLE<TArguments...>, TImplementation*> Construct( void* memory, TArguments&&... arguments )
		{
			EXPECTS_DEBUG( memory != nullptr );
			return new( memory ) TImplementation( std::forward<TArguments>( arguments )... );
		}

		// Brace initialization, in case of  `TImplementation` is an aggregate type and has no user-defined constructor with given arguments.
		template< typename... TArguments >
		static inline std::enable_if_t<!IS_CONSTRUCTIBLE<TArguments...>, TImplementation*> Construct( void* memory, TArguments&&... arguments )
		{
			EXPECTS_DEBUG( memory != nullptr );
			return new( memory ) TImplementation{ std::forward<TArguments>( arguments )... };
		}
	};
}
}
}
}
