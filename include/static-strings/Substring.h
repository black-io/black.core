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
	// Substring extracting trait.
	template< size_t POSITION, size_t LENGTH, typename TString >
	struct Substring;

	// First endpoint of deducing, where the substring begins at the middle of initial string.
	template< size_t POSITION, size_t LENGTH, char... CHARS >
	struct Substring< POSITION, LENGTH, Black::StaticString<CHARS...> >
	{
		// Substring of initial one, where the prefix of `POSITION` length is removed.
		using UnprefixedString = typename Bisect<POSITION, false, Black::StaticString<>, Black::StaticString<CHARS...>>::RightString;

		// The resulting substring is the string somewhere at the middle of initial string.
		using String = typename Bisect<LENGTH, LENGTH == 0, Black::StaticString<>, UnprefixedString>::LeftString;
	};

	// Second endpoint of deducing, where the substring begins from initial string.
	template< size_t LENGTH, char... CHARS >
	struct Substring< 0, LENGTH, Black::StaticString<CHARS...> >
	{
		// The substring is the prefix of initial string.
		using String = typename Bisect<LENGTH, LENGTH == 0, Black::StaticString<>, Black::StaticString<CHARS...>>::LeftString;
	};
}


	// Get the substring from initial static string.
	template< size_t POSITION, size_t LENGTH, typename TString >
	using Substring = typename Internal::Substring<POSITION, LENGTH, TString>::String;
}
}
}
}
