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
	template< size_t POSITION, size_t LENGTH, typename TString >
	struct Substring;

	//
	template< size_t POSITION, size_t LENGTH, char... CHARS >
	struct Substring< POSITION, LENGTH, Black::StaticString<CHARS...> >
	{
		//
		using UnprefixedString = typename Bisect<POSITION, false, Black::StaticString<>, Black::StaticString<CHARS...>>::RightString;

		//
		using String = typename Bisect<LENGTH, LENGTH == 0, Black::StaticString<>, UnprefixedString>::LeftString;
	};

	//
	template< size_t LENGTH, char... CHARS >
	struct Substring< 0, LENGTH, Black::StaticString<CHARS...> >
	{
		//
		using String = typename Bisect<LENGTH, LENGTH == 0, Black::StaticString<>, Black::StaticString<CHARS...>>::LeftString;
	};
}


	//
	template< size_t POSITION, size_t LENGTH, typename TString >
	using Substring = typename Traits::Substring<POSITION, LENGTH, TString>::String;
}
}
}
}
