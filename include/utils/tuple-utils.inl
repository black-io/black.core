#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
{
namespace Traits
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
		Traits::ForEach( elements, function, std::index_sequence_for<TArguments...>{} );
	}
}


inline namespace TextUtils
{
namespace Traits
{
	template< typename TChar, typename... TArguments, size_t... INDICES >
	inline std::basic_string<TChar> FormatString(
		Black::RegularStringView<TChar> format,
		const std::tuple<TArguments...>& arguments,
		std::index_sequence<INDICES...>
	)
	{
		return Black::FormatString( format, std::get<INDICES>( arguments )... );
	}
}


	template< typename TChar, typename... TArguments >
	inline std::basic_string<TChar> FormatString( Black::RegularStringView<TChar> format, const std::tuple<TArguments...>& arguments )
	{
		return Traits::FormatString( format, arguments, std::index_sequence_for<TArguments...>{} );
	}
}
}
}
