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
	// Bisect the static string.
	template< size_t POSITION, bool IS_ENDED, typename TLeftString, typename TRightString >
	struct Bisect;

	// First endpoint path of deducing, where the counter is higher than the length of bisected string.
	template< size_t POSITION, char... STORED_CHARS >
	struct Bisect< POSITION, false, Black::StaticString<STORED_CHARS...>, Black::StaticString<> >
	{
		// Total input string at the left.
		using LeftString	= Black::StaticString<STORED_CHARS...>;

		// Empty string at the right.
		using RightString	= Black::StaticString<>;
	};

	// Second endpoint path of deducing - the position of string bisection is found.
	template< char... STORED_CHARS, char... REST_CHARS >
	struct Bisect< 0, true, Black::StaticString<STORED_CHARS...>, Black::StaticString<REST_CHARS...> >
	{
		// String of required length at the left.
		using LeftString	= Black::StaticString<STORED_CHARS...>;

		// Th rest string at the right.
		using RightString	= Black::StaticString<REST_CHARS...>;
	};

	// Common path of deducing - just walk through chars with counter.
	template< size_t POSITION, char CURRENT_CHAR, char... STORED_CHARS, char... REST_CHARS >
	struct Bisect< POSITION, false, Black::StaticString<STORED_CHARS...>, Black::StaticString<CURRENT_CHAR, REST_CHARS...> >
		: Bisect< POSITION - 1, POSITION == 1, Black::StaticString<STORED_CHARS..., CURRENT_CHAR>, Black::StaticString<REST_CHARS...> >
	{};
}


	/**
		@brief	Bisect the string.
		This trait consists of two inner types : `LeftString` and `RightString`.
		Each of inner types represents the part of given static string being bisected at given position.
	*/
	template< size_t POSITION, typename TString >
	using Bisect = Internal::Bisect<POSITION, POSITION == 0, Black::StaticString<>, TString>;
}
}
}
}
