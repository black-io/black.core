#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	//
	template< typename TCharType, typename TChatTraits = std::char_traits<TCharType> >
	class RegularStringView final
	{

	};

	//
	using StringView	= RegularStringView<char>;

	//
	using StringViewW	= RegularStringView<wchar_t>;

	//
	using StringViewU16	= RegularStringView<char16_t>;

	//
	using StringViewU32	= RegularStringView<char32_t>;
}
}
}
