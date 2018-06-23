#pragma once


namespace Black
{
inline namespace Core
{
inline namespace TextUtils
{
namespace StaticStrings
{
namespace Internal
{
	// Combine the collection of static strings.
	template< typename... TStrings >
	struct Join;

	// Result of strings combination.
	template< char... CHARS >
	struct Join< Black::StaticString<CHARS...> >
	{
		// The result of combination.
		using String = Black::StaticString<CHARS...>;
	};

	// Combine two strings.
	template< char... LEFT_CHARS, char... RIGHT_CARS >
	struct Join< Black::StaticString<LEFT_CHARS...>, Black::StaticString<RIGHT_CARS...> >
	{
		// The result of combination.
		using String = Black::StaticString<LEFT_CHARS..., RIGHT_CARS...>;
	};

	// Unroll the collection of strings and combine it one by one.
	template< char... CHARS, typename... TStrings >
	struct Join< Black::StaticString<CHARS...>, TStrings... >
	{
		using String = typename Join< Black::StaticString<CHARS...>, typename Join<TStrings...>::String >::String;
	};
}


	// Join the collection of static strings.
	template< typename... TStrings >
	using Join = typename Internal::Join<TStrings...>::String;
}
}
}
}
