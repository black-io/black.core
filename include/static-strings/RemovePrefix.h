#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticStrings
{
	// Remove the string prefix.
	template< size_t PREFIX_LENGTH, typename TString >
	using StaticStringRemovePrefix = typename StaticStringBisect<PREFIX_LENGTH, TString>::RightString;
}
}
}
