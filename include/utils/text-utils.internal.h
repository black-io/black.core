namespace Black::Core::TextUtils
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
		// Regular suitable string view type.
		using View		= std::basic_string_view<TChar, TTraits>;

		// Regular suitable string storage type.
		using Storage	= std::basic_string<TChar, TTraits, TAllocator>;
	};


	// Information about consumable strings.
	template< typename TCandidate >
	struct StringInfo : public std::false_type
	{
		// TYpe shortcut.
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


	// Whether the type is valid rearrangeable string.
	template< typename TCandidate >
	struct RearrangeStringTest final : public std::false_type {};

	template< typename TChar, typename TTraits >
	struct RearrangeStringTest<Black::RegularStringView<TChar, TTraits>> final : public std::true_type {};

	template< typename TChar, typename TTraits >
	struct RearrangeStringTest<std::basic_string_view<TChar, TTraits>> final : public std::true_type {};

	template< typename TChar, typename TTraits, typename TAllocator >
	struct RearrangeStringTest<std::basic_string<TChar, TTraits, TAllocator>> final : public std::true_type {};


	// Whether the candidate is valid consumable string.
	template< typename TCandidate >
	inline constexpr bool IS_VALID_STRING = StringInfo<std::decay_t<TCandidate>>::value;

	// Whether the candidate is valid consumable string pattern.
	template< typename TCandidate >
	inline constexpr bool IS_VALID_PATTERN = PatternInfo<std::decay_t<TCandidate>>::value;

	// Whether the type is valid rearrangeable string.
	template< typename TCandidate >
	inline constexpr bool IS_REARRANGEABLE = RearrangeStringTest<std::decay_t<TCandidate>>::value;


	// Type translation for consumable strings.
	template< typename TCandidate >
	using StringView = typename StringInfo<std::decay_t<TCandidate>>::View;

	// Type translation for consumable string patterns.
	template< typename TCandidate >
	using PatternView = typename PatternInfo<std::decay_t<TCandidate>>::View;

	// Type translation for storing the consumable strings.
	template< typename TCandidate >
	using StringStorage = typename StringInfo<std::decay_t<TCandidate>>::Storage;
}
}
