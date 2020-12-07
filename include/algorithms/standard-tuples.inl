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
	void ForEach( std::tuple<TArguments...>& elements, const TFunction& function, std::index_sequence<INDICES...> )
	{
		// Folding expressions (C++17) workaround.
		auto ordered_execution = { 0, ( function( std::get<INDICES>( elements ) ), 0 )... };
	}
}


	template< typename TFunction, typename... TArguments >
	void ForEach( std::tuple<TArguments...>& elements, const TFunction& function )
	{
		Internal::ForEach( elements, function, std::index_sequence_for<TArguments...>{} );
	}
}
}
}
