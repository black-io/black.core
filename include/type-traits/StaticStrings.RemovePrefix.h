#pragma once


namespace Black
{
inline namespace Core
{
inline namespace TextUtils
{
namespace StaticStrings
{
	// Remove the string prefix.
	template< size_t PREFIX_LENGTH, typename TString >
	using RemovePrefix = typename Bisect<PREFIX_LENGTH, TString>::RightString;
}
}
}
}
