#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
namespace Internal
{
	// Test that type is the valid character type.
	template< typename TChar >
	struct ValidCharTest : public std::false_type {};

	template<>
	struct ValidCharTest<char> : public std::true_type {};

	template<>
	struct ValidCharTest<wchar_t> : public std::true_type {};

	template<>
	struct ValidCharTest<char16_t> : public std::true_type {};

	template<>
	struct ValidCharTest<char32_t> : public std::true_type {};


	// Adapter to check the char type and qualify the type of suitable string view.
	template< typename TChar, typename TTraits = std::char_traits<TChar>, typename TAllocator = std::allocator<TChar> >
	struct StringViewAdapter : public ValidCharTest<TChar>
	{
		// Regular suitable type of char.
		using Char		= TChar;

		// Regular suitable string view type.
		using View		= std::basic_string_view<TChar, TTraits>;

		// Regular suitable string storage type.
		using Storage	= std::basic_string<TChar, TTraits, TAllocator>;
	};


	// Information about consumable strings.
	template< typename TCandidate >
	struct StringInfo : public std::false_type
	{
		// Type shortcut.
		using Char		= void;

		// Type shortcut.
		using View		= void;

		// Type shortcut.
		using Storage	= void;
	};

	template< typename TChar, typename TTraits >
	struct StringInfo<Black::RegularStringView<TChar, TTraits>> : public StringViewAdapter<TChar, TTraits> {};

	template< typename TChar, typename TTraits >
	struct StringInfo<std::basic_string_view<TChar, TTraits>> : public StringViewAdapter<TChar, TTraits> {};

	template< typename TChar, typename TTraits, typename TAllocator >
	struct StringInfo<std::basic_string<TChar, TTraits, TAllocator>> : public StringViewAdapter<TChar, TTraits, TAllocator> {};

	template< typename TChar >
	struct StringInfo<TChar*> : public StringViewAdapter<TChar> {};

	template< typename TChar >
	struct StringInfo<const TChar*> : public StringViewAdapter<TChar> {};


	// Information about consumable string patterns.
	template< typename TCandidate, bool IS_INTEGRAL = std::is_integral_v<TCandidate> >
	struct PatternInfo final : public StringInfo<TCandidate> {};

	template< typename TCandidate >
	struct PatternInfo<TCandidate, true> final : public ValidCharTest<TCandidate>
	{
		using View = TCandidate;
	};


	// Type adapter to extract character type from arbitrary string.
	template< typename TCandidate, bool IS_INTEGRAL = std::is_integral_v<TCandidate> >
	struct CharInfo final
	{
		// Selective type of string character.
		using Char = std::enable_if_t<StringInfo<TCandidate>::value, typename StringInfo<TCandidate>::Char>;
	};

	template< typename TCandidate >
	struct CharInfo<TCandidate, true> final
	{
		// Selective type of string character.
		using Char = std::enable_if_t<ValidCharTest<TCandidate>::value, TCandidate>;
	};


	// Whether the type is valid rearrangeable string.
	template< typename TCandidate >
	struct RearrangeStringTest final : public std::false_type {};

	template< typename TChar, typename TTraits >
	struct RearrangeStringTest<Black::RegularStringView<TChar, TTraits>> final : public std::true_type {};

	template< typename TChar, typename TTraits >
	struct RearrangeStringTest<std::basic_string_view<TChar, TTraits>> final : public std::true_type {};

	template< typename TChar, typename TTraits, typename TAllocator >
	struct RearrangeStringTest<std::basic_string<TChar, TTraits, TAllocator>> final : public std::true_type {};


	// Whether the type is valid mutable string.
	template< typename TCandidate >
	struct MutableStringTest final : public std::false_type {};

	template< typename TChar, typename TTraits, typename TAllocator >
	struct MutableStringTest<std::basic_string<TChar, TTraits, TAllocator>> final : public std::true_type {};

	template< typename TChar >
	struct MutableStringTest<TChar*> final : public std::true_type {};


	// Character type translation for consumable strings.
	template< typename TCandidate >
	using StringChar = typename CharInfo<std::decay_t<TCandidate>>::Char;

	// Type translation for consumable strings.
	template< typename TCandidate >
	using StringView = typename StringInfo<std::decay_t<TCandidate>>::View;

	// Type translation for consumable string patterns.
	template< typename TCandidate >
	using PatternView = typename PatternInfo<std::decay_t<TCandidate>>::View;

	// Type translation for storing the consumable strings.
	template< typename TCandidate >
	using StringStorage = typename StringInfo<std::decay_t<TCandidate>>::Storage;


	// Whether the candidate is valid consumable string.
	template< typename TCandidate >
	inline constexpr bool IS_VALID_STRING = StringInfo<std::decay_t<TCandidate>>::value;

	// Whether the candidate is valid consumable string pattern.
	template< typename TCandidate >
	inline constexpr bool IS_VALID_PATTERN = PatternInfo<std::decay_t<TCandidate>>::value;

	// Whether the type is valid rearrangeable string.
	template< typename TCandidate >
	inline constexpr bool IS_REARRANGEABLE = RearrangeStringTest<std::decay_t<TCandidate>>::value;

	// Whether the type is valid mutable string.
	template< typename TCandidate >
	inline constexpr bool IS_MUTABLE = MutableStringTest<std::decay_t<TCandidate>>::value;

	// Whether two strings has same character type.
	template< typename TLeft, typename TRight >
	inline constexpr bool HAS_SAME_CHAR_TYPE = std::is_same_v<StringChar<TLeft>, StringChar<TRight>>;
}
}
}
}
