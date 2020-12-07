#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
namespace Internal
{
	template< typename TFunction, typename... TArguments, size_t... INDICES >
	void ForEach( std::tuple<TArguments...>& elements, TFunction function, std::index_sequence<INDICES...> )
	{
		((void)function( std::get<INDICES>( elements ) ), ...);
	}
}


	template< typename TFunction, typename... TArguments >
	void ForEach( std::tuple<TArguments...>& elements, TFunction&& function )
	{
		Internal::ForEach( elements, std::forward<TFunction>( function ), std::index_sequence_for<TArguments...>{} );
	}
}
}
}
