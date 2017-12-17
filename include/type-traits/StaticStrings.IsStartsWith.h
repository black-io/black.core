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
	//
	template< typename TString, typename TPrefixString >
	struct IsStartsWith;

	//
	template<>
	struct IsStartsWith<Black::StaticString<>, Black::StaticString<>> : std::false_type
	{

	};

	//
	template< char... CHARS >
	struct IsStartsWith<Black::StaticString<CHARS...>, Black::StaticString<>> : std::false_type
	{

	};

	//
	template< char... CHARS >
	struct IsStartsWith<Black::StaticString<>, Black::StaticString<CHARS...>> : std::false_type
	{

	};

	//
	template< char... STRING_CHARS, char... PATTERN_CHARS >
	struct IsStartsWith<Black::StaticString<STRING_CHARS...>, Black::StaticString<PATTERN_CHARS...>>
	{
		//
		using StringPrefix = typename Bisect<sizeof...( PATTERN_CHARS ), false, Black::StaticString<>, Black::StaticString<STRING_CHARS...>>::LeftString;

		//
		constexpr static const bool value = IsEqual<Black::StaticString<PATTERN_CHARS...>, StringPrefix>::value;
	};
}


	//
	template< typename TString, typename TPrefixString >
	constexpr bool IS_STARTS_WITH = Traits::IsStartsWith<TString, TPrefixString>::value;
}
}
}
}
