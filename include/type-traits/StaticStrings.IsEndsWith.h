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
	// Test for string suffix check.
	template< typename TString, typename TPattern >
	struct IsEndsWith;

	// The way to shortcut the empty strings.
	template<>
	struct IsEndsWith<Black::StaticString<>, Black::StaticString<>> : std::false_type
	{

	};

	// The way to shortcut the empty pattern.
	template< char... CHARS >
	struct IsEndsWith<Black::StaticString<CHARS...>, Black::StaticString<>> : std::false_type
	{

	};

	// The way to shortcut the empty string.
	template< char... CHARS >
	struct IsEndsWith<Black::StaticString<>, Black::StaticString<CHARS...>> : std::false_type
	{

	};

	// The way to check that the string suffix is equal to pattern.
	template< char... STRING_CHARS, char... PATTERN_CHARS >
	struct IsEndsWith<Black::StaticString<STRING_CHARS...>, Black::StaticString<PATTERN_CHARS...>>
	{
		// Get the position of string bisection.
		static constexpr size_t BISECT_POSITION = sizeof...( STRING_CHARS ) - std::min( sizeof...( PATTERN_CHARS ), sizeof...( STRING_CHARS ) );

		// Cut off the string prefix.
		using StringSuffix = typename Bisect<BISECT_POSITION, BISECT_POSITION == 0, Black::StaticString<>, Black::StaticString<STRING_CHARS...>>::RightString;

		// Test the equality of string suffix with pattern.
		static constexpr bool value = IsEqual<Black::StaticString<PATTERN_CHARS...>, StringSuffix>::value;
	};
}


	// Check that the static string ends with given pattern.
	template< typename TString, typename TPattern >
	constexpr bool IS_ENDS_WITH = Traits::IsEndsWith<TString, TPattern>::value;
}
}
}
}
