#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticStrings
{
namespace Internal
{
	// Test for equal strings.
	// There is no easy way to use combination of 'same-type' checks. The types have to be recognized as static strings and compared by chars.
	template< typename TLeft, typename TRight >
	struct IsEqual;

	// Path of different strings.
	template< char... LEFT_CHARS, char... RIGHT_CHARS >
	struct IsEqual< Black::StaticString<LEFT_CHARS...>, Black::StaticString<RIGHT_CHARS...> > : std::false_type
	{

	};

	// Path of same strings.
	template< char... CHARS >
	struct IsEqual< Black::StaticString<CHARS...>, Black::StaticString<CHARS...> > : std::true_type
	{

	};
}


	// Whether the two static strings consists of same chars.
	template< typename TLeft, typename TRight >
	inline constexpr bool STATIC_STRING_IS_EQUAL = Internal::IsEqual<TLeft, TRight>::value;
}
}
}
