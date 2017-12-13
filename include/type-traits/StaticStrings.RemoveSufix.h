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
	// Remove the string suffix.
	template< size_t SUFFIX_LENGTH, bool IS_ENABLED, char... CHARS >
	struct RemoveSuffix;

	// Fist path of deducing - the given string is long enough, so the suffix may be removed.
	template< size_t SUFFIX_LENGTH, char... CHARS >
	struct RemoveSuffix< SUFFIX_LENGTH, true, CHARS... >
	{
		// Cropped string.
		using String = typename Bisect<sizeof...( CHARS ) - SUFFIX_LENGTH, false, Black::StaticString<>, Black::StaticString<CHARS...>>::LeftString;
	};

	// Second path of deducing - the required length if higher than the length of string.
	template< size_t SUFFIX_LENGTH, char... CHARS >
	struct RemoveSuffix< SUFFIX_LENGTH, false, CHARS... >
	{
		// Empty string.
		using String = Black::StaticString<>;
	};

	// Guard for suffix removing routine.
	template< size_t SUFFIX_LENGTH, typename TString >
	struct SafeRemoveSuffix;

	// The checking path - compare the length of string with requested length of suffix.
	template< size_t SUFFIX_LENGTH, char... CHARS >
	struct SafeRemoveSuffix< SUFFIX_LENGTH, Black::StaticString<CHARS...> >
		: RemoveSuffix< SUFFIX_LENGTH, ( sizeof...( CHARS ) > SUFFIX_LENGTH ), CHARS... >
	{};
}

	// Remove the string suffix.
	template< size_t SUFFIX_LENGTH, typename TString >
	using RemoveSuffix = typename Traits::SafeRemoveSuffix<SUFFIX_LENGTH, TString>::String;
}
}
}
}
