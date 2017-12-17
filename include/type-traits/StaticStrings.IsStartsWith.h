#pragma once


namespace Black
{
inline namespace Core
{
inline namespace TextUtils
{
namespace StaticStrings
{
namespace Traits
{
	// Test for string prefix check.
	template< typename TString, typename TPattern >
	struct IsStartsWith;

	// The way to shortcut the empty strings.
	template<>
	struct IsStartsWith<Black::StaticString<>, Black::StaticString<>> : std::false_type
	{

	};

	// The way to shortcut the empty pattern.
	template< char... CHARS >
	struct IsStartsWith<Black::StaticString<CHARS...>, Black::StaticString<>> : std::false_type
	{

	};

	// The way to shortcut the empty string.
	template< char... CHARS >
	struct IsStartsWith<Black::StaticString<>, Black::StaticString<CHARS...>> : std::false_type
	{

	};

	// The way to check that the string prefix is equal to pattern.
	template< char... STRING_CHARS, char... PATTERN_CHARS >
	struct IsStartsWith<Black::StaticString<STRING_CHARS...>, Black::StaticString<PATTERN_CHARS...>>
	{
		// Cut off the string suffix.
		using StringPrefix = typename Bisect<sizeof...( PATTERN_CHARS ), false, Black::StaticString<>, Black::StaticString<STRING_CHARS...>>::LeftString;

		// Test the equality of string prefix with pattern.
		static constexpr bool value = IsEqual<Black::StaticString<PATTERN_CHARS...>, StringPrefix>::value;
	};
}


	// Check that the static string starts with given pattern.
	template< typename TString, typename TPattern >
	constexpr bool IS_STARTS_WITH = Traits::IsStartsWith<TString, TPattern>::value;
}
}
}
}
